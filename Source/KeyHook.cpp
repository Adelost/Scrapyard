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
    for (Key key : m_hardwareKeys) {
        if (isModKey(key)) {
            mods.insert(key);
        }
    }
    // Shift acts as a soft modifier
    if (mods.size() == 1 && mods.count(Shift) > 0) {
        mods.erase(Shift);
    }
    for (Key mod : mods) {
        m_hardwareKeys.erase(mod);
        rawSend(mods, false);
    }

    return mods;
}

std::set<Key> KeyHook::getModKeys() {
    std::set<Key> mods;
    for (Key key : m_hardwareKeys) {
        if (isModKey(key)) {
            m_hardwareKeys.insert(key);
        }
    }
    return mods;
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
    m_window = "Spoof";
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
void KeyHook::unmute(Key key) {
//    std::cout << "unmuted: " << key.toStr() << std::endl;
    m_mutedKeys.erase(key);
}
bool KeyHook::isMuted(Key key) {
    return m_mutedKeys.count(key) > 0;
}

void KeyHook::postScript() {
    if (!isMuted(currentKey())) {
        std::cout << "=";
        rawSend(currentKey(), isPressed());
    } else {
        if (!isPressed()) {
            unmute(currentKey());
        }
    }
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
#ifdef _WIN32_
        interceptionSend(key, pressed);
#endif
    }
    std::cout << "=> " << key.toStr() << " " << pressed << std::endl;
}
void KeyHook::on(Condition given, Action then, Action otherwise) {
    std::string path = m_callPath;
    int callCode = given.call();
    if (callCode == 1) {
        if (given.isMuting()) {
            mute(currentKey());
        }
        unTrack(path + "2");
        m_callPath += "1";
        track(then);
    } else if (callCode == 0) {
        unTrack(path + "1");
        m_callPath += "2";
        track(otherwise);
    }
    m_callPath = path + "0\n";
}
bool KeyHook::isWindow(std::string windowName) {
    return currentWindow() == windowName;
}
bool KeyHook::isPressed(Keys keys) {
    if (keys.list.empty()) {
        return true;
    }
    for (Key key : keys.list) {
        if (!s_hook->isPressed(key)) {
            return false;
        }
    }
    return true;
}
void KeyHook::mute(Key key) {
//    std::cout << "muted: " << key.toStr() << std::endl;
    m_mutedKeys.insert(key);
}


int Condition::call() {
    return m_pressCode;
}


Condition::Condition(Keys keys) : Condition(s_hook->getPressCode(keys)) {}

void Action::call(std::string path) {
    m_path = path;
    if (!m_empty) {
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

void ActionTracker::unTrack(KeyHook& hook, std::string path) {
    for (int i = 0; i < m_active.size();) {
        if (m_active[i].withinPath(path)) {
            Action active = m_active[i];
            m_active.erase(m_active.begin() + i);
            active.call(m_active[i].path());
//            active.mute();
            continue;
        }
        i += 1;
    }
}
void ActionTracker::track(std::string callPath, Action action) {
    action.call(callPath);
    if (!isActive(action)) {
        m_active.push_back(action);
    }
}

}