#include "KeyHook.h"
#include "Utils/List.h"

#ifdef _WIN32_

#include <Windows.h>
#include <interception.h>

#endif

namespace kh {

#ifdef _WIN32_
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
#ifdef _WIN32_
    char wnd_title[1024];
    HWND hwnd = GetForegroundWindow();
    GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
    std::string path(wnd_title);
    std::string title = path.substr(path.find_last_of("\\/") + 1, std::string::npos);
    return title;
#else
    return "";
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
    m_sendBuffer.push_back({key, pressed, true});
}

void KeyHook::sendKey(Key key) {
    m_sendBuffer.push_back({key, isPressed(), false});
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
    rawSend(mods, false);
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
    if (isPressed(key) && !isKeyCaptured(key)) {
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

void KeyHook::rawSend(std::set<Key> keys, bool pressed) {
    for (auto key : keys) {
        rawSend(key, pressed);
    }
}

void KeyHook::start() {
#ifdef _WIN32_
    s_context = interception_create_context();
    interception_set_filter(s_context, interception_is_keyboard, INTERCEPTION_FILTER_KEY_ALL);
    while (interception_receive(s_context, s_device = interception_wait(s_context), (InterceptionStroke*) &s_stroke,
                                1) > 0) {
        s_hook = this;
        s_hook->m_currentKey = interceptionGetCurrentKey(s_stroke);
        s_hook->m_pressed = interceptionGetIsPressed(s_stroke);
        s_hook->m_window = getActiveWindow();
        s_hook->preScript();
        s_hook->script();
        s_hook->postScript();
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
    postScript();
    m_debug = false;
}


void KeyHook::preScript() {
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
        rawSend(key, true);
    }
}
void KeyHook::captureKey(Key key) {
    std::cout << "captured: "<< key.toStr() << std::endl;
    m_capturedKeys.insert(key);
}
void KeyHook::releaseKey(Key key) {
    std::cout << "relesed: "<< key.toStr() << std::endl;
    m_capturedKeys.erase(key);
}
bool KeyHook::isKeyCaptured(Key key) {
    return m_capturedKeys.count(key) > 0;
}

void KeyHook::postScript() {
    if (!isKeyCaptured(currentKey())) {
//        std::cout << "-> " << currentKey().toStr() << " " << isPressed() << std::endl;
//        rawSend(currentKey(), isPressed());
        if (!m_debug) {
            interceptionSend(currentKey(), isPressed());
        }
        std::cout << "-> " << currentKey().toStr() << " " << isPressed() << std::endl;
    }
    m_capturedKeys.clear();
    for (QueuedKey q: m_sendBuffer) {
        if (q.blind) {
            rawSend(currentKey(), isPressed());
        } else {
            std::set<Key> modKeys = extractModKeys();
            rawSend(q.key, q.pressed);
            insertKeys(modKeys);
        }
    }
    m_sendBuffer.clear();
}
void KeyHook::rawSend(Key key, bool pressed) {
    if (!m_debug) {
        interceptionSend(key, pressed);
    }
    std::cout << "=> " << key.toStr() << " " << pressed << std::endl;
}
void KeyHook::on(Condition given, Action then, Action otherwise) {
    std::string path = m_callPath;
    int callCode = given.call();
    bool capture = given.captureKey();
    if (callCode == 1) {
        unTrack(path + "2");
        m_callPath += "1";
        track(then, capture);
    } else if (callCode == 0) {
        unTrack(path + "1");
        m_callPath += "2";
        track(otherwise, false);
    }
    m_callPath = path + "0\n";
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
    m_interceptKey = true;
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
    if (!m_empty) {
        m_path = path;
        m_callback();
    }
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
void Action::captureKey() {
    m_capturedKey = s_hook->currentKey();
    s_hook->captureKey(m_capturedKey);
    m_hasCapturedKey = true;

}
void Action::releaseKey() {
    if (m_hasCapturedKey) {
        s_hook->releaseKey(m_capturedKey);
        m_hasCapturedKey = false;
    }
}

void ActionTracker::unTrack(KeyHook& hook, std::string path) {
    for (int i = 0; i < m_active.size();) {
        if (m_active[i].withinPath(path)) {
            Action active = m_active[i];
            m_active.erase(m_active.begin() + i);
            active.call(m_active[i].path());
            active.releaseKey();
            continue;
        }
        i += 1;
    }
}
void ActionTracker::track(std::string callPath, Action action, bool capture) {
    if (capture) {
        action.captureKey();
    }
    action.call(callPath);
    if (!isActive(action)) {
        m_active.push_back(action);
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