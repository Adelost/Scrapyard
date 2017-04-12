#pragma once

#include <iostream>
#include <functional>
#include <set>
#include <vector>
#include <initializer_list>


//enum class Key {
//    ARROW_LEFT = 37,
//    ARROW_UP = 38,
//    ARROW_RIGHT = 39,
//    ARROW_DOWN = 40,
//    WINDOWS = 92,
//    LSHIFT = 160,
//    RSHIFT = 161,
//    LCTRL = 162,
//    RCTRL = 163,
//    LALT = 164,
//    RALT = 165
//};

//
//Keys operator+(const Keys& left, const Key& right) {
//    return Keys();
//}


class Keys;

class Key {
public:
    Key(char code) {
        m_code = code;
    }

    std::vector<int> combo;

private:
    char m_code;

};

class Keys {
public:
    Keys(){};
    std::vector list;
};


Keys operator+(const Key& left, const Key& right) {
    Keys keys;
    keys.list.push_back({left, right});
    return keys;
}

Keys operator+(const Keys& keys, const Key& key) {
    keys.list.push_back(key);
    return keys;
}


//class Context {
//public:
//    Context(KeyHook hook) {
//        m_hook = hook;
//    }
//    bool pressed;
//    bool ctrl;
//    bool shift;
//    bool alt;
//    bool handled;
//    std::string window;
//
//    std::string callpath;
//
//    bool key(Key key) { m_hook.isKey(key) };
//
//private:
//    KeyHook m_hook;
//
//};
class KeyHook;

class Window {
public:
    explicit Window(std::string name) {
        m_name = name;
    }
    const std::string name() {
        return m_name;
    }
private:
    std::string m_name;
};

class Condition {
public:
    Condition() {
        m_callback = [] { return true; };
    }
    Condition(std::function<bool()> callback) {
        m_callback = callback;
    }
    Condition(Keys keys) {
    }
    Condition(std::initializer_list<Key> keys);
    Condition(Key key) : Condition({key}) {}
    Condition(Window window);
    bool call();

private:
    std::function<bool()> m_callback;
};

class Action {
public:
    Action() {}
    Action(Key key) : Action({key}) {}
    Action(std::function<void()> callback) {
        m_callback = callback;
    }
    Action(std::initializer_list<Key> keys);
    void call(std::string path);
    bool isActive(std::string path) {
        for (int i = 0; i < path.length(); i += 1) {

        }
    }
    std::string path() const { return m_path; };
    bool withinPath(std::string path);

private:
    std::function<void()> m_callback = [] {};
    std::string m_path = "";
};

class ActionTracker {
public:
    std::vector<Action> m_active;
    void track(const Action action) {
        if (!isActive(action)) {
            m_active.push_back(action);
//            std::cout << "tracked: " << action.path() << std::endl;
        }
    }
    void unTrack(KeyHook& hook, std::string path);
    bool isActive(const Action action) {
        for (Action active: m_active) {
            if (active.path() == action.path()) {
                return true;
            }
        }
        return false;
    }
};


class KeyHook {
public:
    KeyHook() {
        std::cout << "Keyhook consturcted" << std::endl;
    }
    virtual ~KeyHook() {}
    bool isKey(Key key);
    Key currentKey() { return m_key; };
    void start();
    bool isPressed() { return m_pressed; }
    std::string window() { return m_window; }
    void debug(Key key, bool pressed);
    std::string callPath() { return m_callPath; };
    void sendKey(Key key);

    Key A = Key("a");
    Key B = Key("b");
    Key C = Key("c");
    Key D = Key("d");
    Key E = Key("e");
    Key F = Key("f");
    Key G = Key("g");
    Key H = Key("h");
    Key I = Key("i");
    Key J = Key("j");
    Key K = Key("k");
    Key L = Key("l");
    Key M = Key("m");
    Key N = Key("n");
    Key O = Key("o");
    Key P = Key("p");
    Key Q = Key("q");
    Key R = Key("r");
    Key S = Key("s");
    Key T = Key("t");
    Key U = Key("u");
    Key V = Key("v");
    Key W = Key("w");
    Key X = Key("x");
    Key Y = Key("y");
    Key Z = Key("z");
    Key Ctrl = Key::LCTRL;
    Key Alt = Key::LALT;
    Key Shift = Key::LSHIFT;
    Key ArrowUp = Key::ARROW_UP;
    Key ArrowLeft = Key::ARROW_LEFT;
    Key ArrowDown = Key::ARROW_DOWN;
    Key ArrowRight = Key::ARROW_RIGHT;

private:
    void preScript();
    std::set<Key> unsetModKeys();
    void extractIfPressed(std::set<Key>& out, Key key);
    void sendKeyBlind(Key key, bool pressed);
    void sendKeysBlind(std::set<Key> keys, bool pressed);

    bool m_pressed;
    std::string m_window;
    bool m_handled;
    Key m_key;
    std::string m_callPath = "";
    std::set<Key> m_hardwareKeys;
    ActionTracker m_actionTracker;
    bool m_debug = false;
    bool m_injected = false;


protected:
    virtual void script() = 0;
    void on(Condition given, Action then, Action otherwise = Action()) {
        std::string path = m_callPath;
        if (given.call()) {
            m_actionTracker.unTrack(*this, path + "2");
            m_callPath += "1";
            then.call(m_callPath);
            m_actionTracker.track(then);
        } else {
            m_actionTracker.unTrack(*this, path + "1");
            m_callPath += "2";
            otherwise.call(m_callPath);
            m_actionTracker.track(otherwise);
        }
        m_callPath = path + "0";
    }
};

