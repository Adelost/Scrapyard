#include "KeyHook.h"
#include <Windows.h>
#include <ctype.h>

#include "Utils/List.h"

using namespace std;

#include <set>

static set<Key> s_hardwareKeys;
static set<Key> s_virtualKeys;
static std::function<void(KeyEvent&)> s_callback;

void KeyHook::run(std::function<void(KeyEvent&)> callback) {
    s_callback = callback;
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, [](int nCode, WPARAM wParam, LPARAM lParam) -> LRESULT CALLBACK {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*) lParam;
        bool isInjected = (p->flags & LLKHF_INJECTED) == 1;
        if (nCode == HC_ACTION && !isInjected) {
            KeyEvent event = {Key(0)};
            bool isValid = true;
            switch (wParam) {
                case WM_KEYDOWN:
                case WM_SYSKEYDOWN:
                    event.pressed = true;
                    break;
                case WM_KEYUP:
                case WM_SYSKEYUP:
                    break;
                default:
                    isValid = false;
                    break;
            }
            if (isValid) {
                event.window = KeyHook::getActiveWindowTitle();
                event.key = (Key) tolower((int) p->vkCode);
                cout << "in: " << (unsigned char)p->vkCode << endl;
                if (event.pressed) {
                    s_hardwareKeys.insert(event.key);
                } else {
                    s_hardwareKeys.erase(event.key);
                }
                event.shift = isPressed(Key::LSHIFT) || isPressed(Key::RSHIFT);
                event.ctrl = isPressed(Key::LCTRL) || isPressed(Key::RCTRL);
                event.alt = isPressed(Key::LALT) || isPressed(Key::RALT);
                s_callback(event);
                if (event.handled) {
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
}

std::string KeyHook::getActiveWindowTitle() {
    char wnd_title[1024];
    HWND hwnd = GetForegroundWindow();
    GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
    std::string path(wnd_title);
    string title = path.substr(path.find_last_of("\\/") + 1, string::npos);
    return title;
}

void KeyHook::sendKeyBlind(Key key, bool pressed) {
    INPUT in = {0};
    in.type = INPUT_KEYBOARD;
    in.ki.dwExtraInfo = 0;
    if (!pressed) {
        in.ki.dwFlags = KEYEVENTF_KEYUP;
    }
    in.ki.wVk = (WORD) toupper((int) key);
    SendInput(1, &in, sizeof(INPUT));
    cout << "send: " << (unsigned char)key << " " << pressed << endl;
}


void KeyHook::swap(KeyEvent& event, Key from, Key to) {
    if (event.key == from) {
        event.handled = true;
        sendKey(to, event.pressed);
    }
}

void KeyHook::sendKey(Key key, bool pressed) {
//    ae::List<WORD> wordList(s_hardwareKeys);
//    cout << wordList.toString() << endl;

    auto modKeys = unsetModKeys();
    sendKeyBlind(key, pressed);
    sendKeysBlind(modKeys, true);
    if (pressed) {
        s_virtualKeys.insert(key);
//        unsigned char keyChar = (unsigned char) key;
    } else {
        s_virtualKeys.erase(key);
    }
}

bool KeyHook::isPressed(Key key) {
    return s_hardwareKeys.count(key) > 0;
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
    if (isPressed(key)) {
        out.insert(keyCode);
        s_hardwareKeys.erase(keyCode);
    }
}


void KeyHook::sendKeysBlind(std::set<Key> keys, bool pressed) {
    for (auto key : keys) {
        sendKeyBlind(key, pressed);
    }
}
set<Key> KeyHook::getVirtualKeys() {
    return s_virtualKeys;
}
bool KeyEvent::isPressed(Key key1) {
    KeyHook::isPressed(key);
}
