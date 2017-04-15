#include "KeyHook.h"
#include <ctype.h>
#include "Utils/List.h"
#include <set>

#ifndef _LINUX_

#include <Windows.h>

#endif

using namespace std;

namespace kh {

std::string getActiveWindow() {
#if _LINUX_
    return "";
#else
    char wnd_title[1024];
    HWND hwnd = GetForegroundWindow();
    GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
    std::string path(wnd_title);
    string title = path.substr(path.find_last_of("\\/") + 1, string::npos);
    return title;
#endif
}

static KeyHook* s_hook;

bool startsWith(string str, string prefix) {
    if (str.length() < prefix.length()) {
        return false;
    }
    for (int i = 0; i < prefix.length(); i += 1) {
        if (str[i] != prefix[i]) {
            return false;
        }
    }
    return true;
}


void KeyHook::sendKeyBlind(Key key, bool pressed) {
#if _LINUX_
#else
    if (!m_debug) {
        INPUT in = {0};
        in.type = INPUT_KEYBOARD;
        in.ki.dwExtraInfo = 0;
        if (!pressed) {
            in.ki.dwFlags = KEYEVENTF_KEYUP;
        }
        in.ki.wVk = (WORD) key.getCode();
        cout << "-> " << key.toChar() << " " << pressed << endl;
        m_injected = true;
        SendInput(1, &in, sizeof(INPUT));
        m_injected = false;
    }
#endif
}


void KeyHook::sendKey(Key key) {
    std::set<Key> modKeys = extractModKeys();
    sendKeyBlind(key, isPressed());
    insertKeys(modKeys);
    m_handled = true;
}

bool KeyHook::isKey(Key key) {
    return m_hardwareKeys.count(key) > 0;
}

set<Key> KeyHook::extractModKeys() {
    set<Key> mods;
    extractKey(mods, Key(KeyCode::LSHIFT));
    extractKey(mods, Key(KeyCode::RSHIFT));
    extractKey(mods, Key(KeyCode::LCTRL));
    extractKey(mods, Key(KeyCode::RCTRL));
    extractKey(mods, Key(KeyCode::LALT));
    extractKey(mods, Key(KeyCode::RALT));
    sendKeysBlind(mods, false);
    return mods;
}

set<Key> KeyHook::getModKeys() {
    set<Key> mods;
    getKey(mods, Key(KeyCode::LSHIFT));
    getKey(mods, Key(KeyCode::RSHIFT));
    getKey(mods, Key(KeyCode::LCTRL));
    getKey(mods, Key(KeyCode::RCTRL));
    getKey(mods, Key(KeyCode::LALT));
    getKey(mods, Key(KeyCode::RALT));
    return mods;
}

void KeyHook::extractKey(set<Key>& out, Key key) {
    Key keyCode = key;
    if (isKey(key)) {
        out.insert(keyCode);
        m_hardwareKeys.erase(keyCode);
    }
}

void KeyHook::getKey(set<Key>& out, Key key) {
    Key keyCode = key;
    if (isKey(key)) {
        out.insert(keyCode);
    }
}

void KeyHook::sendKeysBlind(std::set<Key> keys, bool pressed) {
    for (auto key : keys) {
        sendKeyBlind(key, pressed);
    }
}

void KeyHook::start() {
    s_hook = this;
#if _LINUX_
#else
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, [](int nCode, WPARAM wParam, LPARAM lParam) -> LRESULT CALLBACK {


        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*) lParam;
        cout << "<= " << (unsigned char)tolower((int) p->vkCode) << " " << s_hook->isPressed() << endl;
        cout << "code: " << nCode << endl;
        cout << "param: " << wParam << endl;
        bool isInjected = (bool)(p->flags & LLKHF_INJECTED);
        cout << "LLKHF_EXTENDED: " << (bool)(p->flags & LLKHF_EXTENDED) << endl;
        cout << "LLKHF_INJECTED: " << (bool)(p->flags & LLKHF_INJECTED) << endl;
        cout << "LLKHF_ALTDOWN: " << (bool)(p->flags & LLKHF_ALTDOWN) << endl;


        cout << "LLKHF_UP: " << (bool)(p->flags & LLKHF_UP) << endl;

        if (nCode == HC_ACTION && !s_hook->m_injected) {
            bool isValid = true;
            switch (wParam) {
                case WM_KEYDOWN:
                case WM_SYSKEYDOWN:
                    s_hook->m_pressed = true;
                    break;
                case WM_KEYUP:
                case WM_SYSKEYUP:
                    s_hook->m_pressed = false;
                    break;
                default:
                    isValid = false;
                    break;
            }
            if (isValid) {
                s_hook->m_currentKey = tolower((int) p->vkCode);
                s_hook->m_window = getActiveWindow();
                s_hook->preScript();
                s_hook->script();
            }
        }
        if (s_hook->m_handled) {
            cout << "#HANDLED" << endl;
            return 1;
        }
        if (s_hook->m_handled) {
            cout << "#INJECTED" << endl;
            return 1;
        }
        cout << "=> " << s_hook->currentKey().toChar() << " " << s_hook->isPressed() << endl;
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }, NULL, 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hook);
#endif
}

void KeyHook::debug(Key key, bool pressed) {
    s_hook = this;
    m_debug = true;
    m_currentKey = key;
    m_pressed = pressed;
    m_window = "debug";
    preScript();
    script();
    m_debug = false;
}

void KeyHook::preScript() {
    s_hook = this;
    m_handled = false;
    m_callPath = "";
    if (m_pressed) {
        m_hardwareKeys.insert(m_currentKey);
    } else {
        m_hardwareKeys.erase(m_currentKey);
    }
}
void KeyHook::insertKeys(std::set<Key> keys) {
    for (Key key : keys) {
        m_hardwareKeys.insert(key);
        sendKeyBlind(key, true);
    }
}

bool Condition::call() {
    return m_callback();
}


Condition::Condition(Window window) {
    m_callback = [&] {
        return s_hook->currentWindow() == window.name();
    };
}
Condition::Condition(Keys keys) {
    m_callback = [keys] {
        for (Key key : keys.list) {
            if (!s_hook->isKey(key)) {
                return false;
            }
        }
        if (!keys.isCurrentModifiers()) {
            return false;
        }
        if (!keys.isCurrentKey()) {
            cout << "Not current: " << keys.list.back().toChar() << endl;
            return false;
        }
        return true;
    };
}

void Action::call(std::string path) {
    m_path = path;
    m_callback();
}

Action::Action(std::initializer_list<Key> keys) {
    std::vector<Key> keysCopy = keys;
//    std::cout << "action:";
//    for (Key key : keysCopy) {
//       std::cout << (unsigned char)key;
//    }
//    std::cout << endl;
    m_callback = [keysCopy] {
//        std::cout << "actioncb:";
//        for (Key key : keysCopy) {
//            std::cout << (unsigned char)key;
//        }
//        std::cout << endl;
        for (Key key : keysCopy) {
            s_hook->sendKey(key);
        }
    };
}
bool Action::withinPath(string path) {
    return startsWith(m_path, path);
}
void ActionTracker::unTrack(KeyHook& hook, std::string path) {
    for (int i = 0; i < m_active.size();) {
        if (m_active[i].withinPath(path)) {
            m_active[i].call(path);
            m_active.erase(m_active.begin() + i);
            continue;
        }
        i += 1;
    }
}

bool Keys::isCurrentKey() const {
    if (list.empty()) {
        return true;
    }
//    cout << "Curr: " << list.back().toChar() << " " << s_hook->currentKey().toChar() << endl;
    return list.back().getCode() == s_hook->currentKey().getCode();
}
bool Keys::isCurrentModifiers() const {
    set<Key> mods = s_hook->getModKeys();
    for (Key key: list) {
        mods.erase(key);
    }
    return mods.empty();
}
}