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
    int code = (int) key.getCode();
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

ScanCode charToScanCode(char c) {
#ifdef _WIN32_
    SHORT virtualKey = VkKeyScan(c);
    UINT scanCode = MapVirtualKey((UINT) virtualKey, 0);
    return (ScanCode) scanCode;
#else
    return (ScanCode)c;
#endif
}

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

void KeyHook::sendBlind(Key key, bool pressed) {
    m_sendBuffer.push_back({key, pressed, true});
}

void KeyHook::send(Key key, bool pressed) {
    m_sendBuffer.push_back({key, pressed, false});
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
    if (mods.size() == 1 && mods.count(LShift) > 0) {
        mods.erase(LShift);
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
            mods.insert(key);
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
        s_hook->m_currentKey = (ScanCode) interceptionGetCurrentKey(s_stroke);
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
    std::cout << "unmuted: " << key.toStr() << std::endl;
    m_mutedKeys.erase(key);
}
bool KeyHook::isMuted(Key key) {
    return m_mutedKeys.count(key) > 0;
}

void KeyHook::postScript() {
    bool unmuted = false;
    if (!isMuted(currentKey())) {
        std::cout << "=";
        if (isStashedMods()) {
            unstashMods();
        }
        rawSend(currentKey(), isPressed());
    } else {
        if (!isPressed()) {
            unmute(currentKey());
            unmuted = true;
        }
    }
    std::set<Key> modKeys;
    for (QueuedKey q: m_sendBuffer) {
        if (q.blind) {
            if (isStashedMods()) {
                unstashMods();
            }
            rawSend(q.key, q.pressed);
        } else {
            if (!isStashedMods()) {
                stashMods();
            }
            rawSend(q.key, q.pressed);
        }
    }

    if (unmuted && isStashedMods()) {
        unstashMods();
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
        then.call(m_callPath);
    } else if (callCode == 0) {
        unTrack(path + "1");
        m_callPath += "2";
        otherwise.call(m_callPath);
    }
    m_callPath = path + "0";
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
    std::cout << "muted: " << key.toStr() << std::endl;
    m_mutedKeys.insert(key);
}
void KeyHook::send(std::string text) {
    for (char c : text) {
        bool upper = isupper(c);
        if (upper) {
            c = (char) tolower(c);
        };
        ScanCode code = charToScanCode(c);
        if (upper) {
            sendBlind(LShift, true);
        }
        send(code, true);
        send(code, false);
        if (upper) {
            sendBlind(LShift, false);
        }
    }
}


int Condition::call() {
    return m_pressCode;
}


Condition::Condition(Keys keys) : Condition(s_hook->getPressCode(keys)) {}

void Action::call(std::string path) {
    m_path = path;
    if (!m_noActivate) {
        m_activate();
    }
}

Action::Action(Keys keys) {
    m_activate = [=] {
        s_hook->send(keys, true);
        s_hook->track([=] {
            s_hook->send(keys, false);
        });
    };
    m_noActivate = false;
}
Action::Action(bool& toggle) {
    m_activate = [&] {
        toggle = !toggle;
    };
    m_noActivate = false;
}
Action::Action(std::string text) {
    m_activate = [=] {
        s_hook->send(text);
    };
    m_noActivate = false;
}

void PathTracker::unTrack(std::string path) {
    for (int i = 0; i < m_tracked.size();) {
        Tracked& tracked = m_tracked[i];
        if (withinPath(tracked, path)) {
            tracked.callback();
            m_tracked.erase(m_tracked.begin() + i);
//            std::cout << "untrack: " << path << std::endl;
            continue;
        }
        i += 1;
    }
}
bool PathTracker::withinPath(PathTracker::Tracked& tracked, std::string path) {
    return startsWith(tracked.path, path);

}
void PathTracker::track(std::string path, std::function<void()> callback) {
    if (!isTracked(path)) {
        m_tracked.push_back({path, callback});
//        std::cout << "track: " << path << std::endl;
    }
}

}