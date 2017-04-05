#include "KeyHook.h"
#include <Windows.h>
#include <ctype.h>

#include "Utils/List.h"

using namespace std;

#include <set>

static set<unsigned char> s_pressedKeys;
static std::function<void(KeyEvent&)> s_callback;

void KeyHook::run(std::function<void(KeyEvent&)> callback) {
    s_callback = callback;
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, [](int nCode, WPARAM wParam, LPARAM lParam) -> LRESULT CALLBACK {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*) lParam;
        bool isInjected = (p->flags & LLKHF_INJECTED) == 1;
        if (nCode == HC_ACTION && !isInjected) {
            KeyEvent event = {0};
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
                event.key = (unsigned char) tolower((int) p->vkCode);
                if (event.pressed) {
                    s_pressedKeys.insert(event.key);
                } else {
                    s_pressedKeys.erase(event.key);
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

void KeyHook::sendKeyBlind(unsigned char key, bool pressed) {
    INPUT in = {0};
    in.type = INPUT_KEYBOARD;
    in.ki.dwExtraInfo = 0;
    if (!pressed) {
        in.ki.dwFlags = KEYEVENTF_KEYUP;
    }
    in.ki.wVk = (WORD) toupper(key);
    SendInput(1, &in, sizeof(INPUT));
}


void KeyHook::sendKey(unsigned char key, bool pressed) {
//    ae::List<WORD> wordList(s_pressedKeys);
//    cout << wordList.toString() << endl;

    auto modKeys = unsetModKeys();
    sendKeyBlind(key, pressed);
    sendKeysBlind(modKeys, true);
}

void KeyHook::swap(KeyEvent& event, unsigned char from, unsigned char to) {
    if (event.key == from) {
        event.handled = true;
        sendKey(to, event.pressed);
    }
}

bool KeyHook::isPressed(Key key) {
    return s_pressedKeys.count((unsigned char) key) > 0;
}

set<unsigned char> KeyHook::unsetModKeys() {
    set<unsigned char> modSet;
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

void KeyHook::extractIfPressed(set<unsigned char>& out, Key key) {
    unsigned char keyCode = (unsigned char) key;
    if (isPressed(key)) {
        out.insert(keyCode);
        s_pressedKeys.erase(keyCode);
    }
}


void KeyHook::sendKeysBlind(std::set<unsigned char> keys, bool pressed) {
    for (auto key : keys) {
        sendKeyBlind(key, pressed);
    }
}
