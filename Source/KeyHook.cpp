#include "KeyHook.h"
#include <ctype.h>
#include "Utils/List.h"
#include <set>

#ifdef _WINDOWS_
#include <Windows.h>
#endif

using namespace std;


std::string getActiveWindow() {
#if _WINDOWS_
    char wnd_title[1024];
    HWND hwnd = GetForegroundWindow();
    GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
    std::string path(wnd_title);
    string title = path.substr(path.find_last_of("\\/") + 1, string::npos);
    return title;
#else
    return "";
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
#if _WINDOWS_
    INPUT in = {0};
    in.type = INPUT_KEYBOARD;
    in.ki.dwExtraInfo = 0;
    if (!pressed) {
        in.ki.dwFlags = KEYEVENTF_KEYUP;
    }
    in.ki.wVk = (WORD) toupper((int) key);
    SendInput(1, &in, sizeof(INPUT));
#endif
    cout << ": " << (unsigned char) key << " " << pressed << endl;
}

void KeyHook::sendKey(Key key) {
    std::cout << "code:" << (int) key << endl;
    if (isPressed()) {
        auto modKeys = unsetModKeys();
        sendKeyBlind(key, true);
        sendKeysBlind(modKeys, true);
    } else {
        sendKeyBlind(key, false);
    }
}

bool KeyHook::isKey(Key key) {
    return m_hardwareKeys.count(key) > 0;
}

set<Key> KeyHook::unsetModKeys() {
    set<Key> modSet;
    extractIfPressed(modSet, Key::WINDOWS);
    extractIfPressed(modSet, Key::LSHIFT);
    extractIfPressed(modSet, Key::RSHIFT);
    extractIfPressed(modSet, Key::LCTRL);
    extractIfPressed(modSet, Key::RCTRL);
    extractIfPressed(modSet, Key::LALT);
    extractIfPressed(modSet, Key::RALT);
    sendKeysBlind(modSet, false);
    return modSet;
}

void KeyHook::extractIfPressed(set<Key>& out, Key key) {
    Key keyCode = key;
    if (isKey(key)) {
        out.insert(keyCode);
        m_hardwareKeys.erase(keyCode);
    }
}

void KeyHook::sendKeysBlind(std::set<Key> keys, bool pressed) {
    for (auto key : keys) {
        sendKeyBlind(key, pressed);
    }
}

void KeyHook::start() {
    s_hook = this;
#if _WINDOWS_
    HHOOK
            hook = SetWindowsHookEx(WH_KEYBOARD_LL, [](int nCode, WPARAM wParam, LPARAM lParam) -> LRESULT
    CALLBACK {
            KBDLLHOOKSTRUCT * p = (KBDLLHOOKSTRUCT*) lParam;
            bool isInjected = (p->flags & LLKHF_INJECTED) == 1;
            if (nCode == HC_ACTION && !isInjected) {
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
                    s_hook->m_key = (Key) tolower((int) p->vkCode);
                    cout << "in: " << (unsigned char) p->vkCode << endl;
                    cout << "in: " << (int) p->vkCode << endl;
                    cout << "in: " << (int) tolower((int) p->vkCode) << endl;
                    cout << "up: " << toupper((int) s_hook->m_key) << endl;
                    s_hook->m_window = getActiveWindow();
                    s_hook->preScript();
                    s_hook->script();
                    if (s_hook->m_handled) {
                        return 1;
                    }
                }
            }
            return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }, 0, 0);
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
    m_key = key;
    m_pressed = pressed;
    m_window = "debug";
    preScript();
    script();
}
void KeyHook::preScript() {
    s_hook = this;
    m_handled = false;
    m_callPath = "";
    if (m_pressed) {
        m_hardwareKeys.insert(m_key);
    } else {
        m_hardwareKeys.erase(m_key);
    }
}

bool Condition::call() {
    return m_callback();
}
Condition::Condition(std::initializer_list<Key> keys) {
    std::vector<Key> keysCopy = keys;
    m_callback = [keysCopy]() {
        for (Key key : keysCopy) {
            if (!s_hook->isKey(key)) {
                return false;
            }
        }
        return true;
    };
}
Condition::Condition(Window window) {
    m_callback = [&] {
        return s_hook->window() == window.name();
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
//            cout << "untrack: " << path << endl;
            continue;
        }
        i += 1;
    }
}
