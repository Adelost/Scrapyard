#include "KeyHook.h"
#include <ctype.h>
#include "Utils/List.h"
#include <set>

#ifndef _LINUX_

#include <Windows.h>
#include <interception.h>

#endif

namespace kh {

#if _LINUX_
#else
InterceptionKeyStroke s_stroke;
InterceptionContext s_context;
InterceptionDevice s_device;

int interceptionGetCurrentKey(InterceptionKeyStroke stroke) {
    int code = stroke.code;
    int state = stroke.state;
    if (state > 1) {
        code += 128;
    }
    return code;
}
bool interceptionGetIsPressed(InterceptionKeyStroke stroke) {
    int state = stroke.state;
    if (state > 1) {
        state -= 2;
    }
    return state == 0;
}
void interceptionSend(Key key, bool pressed) {
    int code = key.getCode();
    int state = !pressed;
    if (code >= 128) {
        code -= 128;
        state += 2;
    }
    InterceptionKeyStroke stroke = s_stroke;
    stroke.code = (unsigned short) code;
    stroke.state = (unsigned short) state;
    interception_send(s_context, s_device, (InterceptionStroke const*) &stroke, 1);;

}
#endif

std::string getActiveWindow() {
#if _LINUX_
    return "";
#else
    char wnd_title[1024];
    HWND hwnd = GetForegroundWindow();
    GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
    std::string path(wnd_title);
    std::string title = path.substr(path.find_last_of("\\/") + 1, std::string::npos);
    return title;
#endif
}

static KeyHook* s_hook;


bool startsWith(std::string str, std::string prefix) {
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
        m_injected = true;
        interceptionSend(key, pressed);
        m_injected = false;
    }
    if (key.toStr() == "D") {
      int i = 0;
    }
    std::cout << "-> " << key.toStr() << " " << isPressed() << std::endl;
#endif
}

void KeyHook::sendKey(Key key) {
    std::set<Key> modKeys = extractModKeys();
    sendKeyBlind(key, isPressed());
    insertKeys(modKeys);
    m_intercepted = true;
}

bool KeyHook::isPressed(Key key) {
    return m_hardwareKeys.count(key) > 0;
}

std::set<Key> KeyHook::extractModKeys() {
    std::set<Key> mods;
    extractKey(mods, KeyCodes::Shift);
    extractKey(mods, KeyCodes::RShift);
    extractKey(mods, KeyCodes::Ctrl);
    extractKey(mods, KeyCodes::RCtrl);
    extractKey(mods, KeyCodes::Alt);
    extractKey(mods, KeyCodes::RAlt);
    sendKeysBlind(mods, false);
    return mods;
}

std::set<Key> KeyHook::getModKeys() {
    std::set<Key> mods;
    getKey(mods, KeyCodes::Shift);
    getKey(mods, KeyCodes::RShift);
    getKey(mods, KeyCodes::Ctrl);
    getKey(mods, KeyCodes::RCtrl);
    getKey(mods, KeyCodes::Alt);
    getKey(mods, KeyCodes::RAlt);
    return mods;
}

void KeyHook::extractKey(std::set<Key>& out, Key key) {
    Key keyCode = key;
    if (isPressed(key)) {
        out.insert(keyCode);
        m_hardwareKeys.erase(keyCode);
    }
}

void KeyHook::getKey(std::set<Key>& out, Key key) {
    Key keyCode = key;
    if (isPressed(key)) {
        out.insert(keyCode);
    }
}

void KeyHook::sendKeysBlind(std::set<Key> keys, bool pressed) {
    for (auto key : keys) {
        sendKeyBlind(key, pressed);
    }
}

void KeyHook::start() {
#if _LINUX_
#else
    s_context = interception_create_context();
    interception_set_filter(s_context, interception_is_keyboard, INTERCEPTION_FILTER_KEY_ALL);
    while (interception_receive(s_context, s_device = interception_wait(s_context), (InterceptionStroke*) &s_stroke,
                                1) > 0) {
        if (m_injected) {
            interception_send(s_context, s_device, (InterceptionStroke const*) &s_stroke, 1);
            continue;
        }
//        std::cout << s_strsoke.code << " " << s_stroke.state << " " << s_stroke.information << std::endl;
        s_hook = this;
        s_hook->m_currentKey = interceptionGetCurrentKey(s_stroke);
        s_hook->m_pressed = interceptionGetIsPressed(s_stroke);
        s_hook->m_window = getActiveWindow();
        s_hook->preScript();
        s_hook->script();
        if (!s_hook->m_intercepted) {
            std::cout << "<> " << currentKey().toStr() << " " << isPressed() << std::endl;
            interception_send(s_context, s_device, (InterceptionStroke const*) &s_stroke, 1);
        }
    }
    interception_destroy_context(s_context);
#endif
}

void KeyHook::spoof(Key key, bool pressed) {
    m_debug = true;
    s_hook = this;
    m_currentKey = key;
    m_pressed = pressed;
    m_window = "debug";
    preScript();
    script();
    if (!m_intercepted) {
        std::cout << "->" << currentKey().toStr() << " " << isPressed() << std::endl;
    }
    m_debug = false;
}


void KeyHook::preScript() {
    m_intercepted = false;
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


int Condition::call() {
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
            if (!s_hook->isPressed(key)) {
                return 0;
            }
        }
        if (!keys.isCurrentModifiers()) {
            return 0;
        }
        if (keys.isCurrentKey()) {
//            std::cout << "Not current: " << keys.list.back().toChar() << std::endl;
            return 1;
        }
        return 2;
    };
}

void Action::call(std::string path) {
    m_path = path;
    m_callback();
}

Action::Action(Keys keys) {
    m_callback = [keys] {
        for (Key key : keys.list) {
            s_hook->sendKey(key);
        }
    };
}
bool Action::withinPath(std::string path) {
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
    std::set<Key> mods = s_hook->getModKeys();
    for (Key key: list) {
        mods.erase(key);
    }
    return mods.empty();
}
}