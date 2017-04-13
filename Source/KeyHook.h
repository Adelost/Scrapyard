#pragma once

#include <iostream>
#include <functional>
#include <set>
#include <vector>
#include <initializer_list>

namespace kh {

enum class KeyCode {
    ARROW_LEFT = 37,
    ARROW_UP = 38,
    ARROW_RIGHT = 39,
    ARROW_DOWN = 40,
    WINDOWS = 92,
    LSHIFT = 160,
    RSHIFT = 161,
    LCTRL = 162,
    RCTRL = 163,
    LALT = 164,
    RALT = 165
};


class Key {
public:
    Key() {
    }
    Key(int code) {
        m_code = code;
    }
    Key(KeyCode code) {
        m_code = (int) code;
    }
    unsigned char toChar() const {
        return (unsigned char) m_code;
    }
    int getCode() const {
        return toupper(m_code);
    }
    bool operator<(const Key& right) const {
        return m_code < right.m_code;
    }
private:
    int m_code;
};

class Keys {
public:
    Keys() {};
    Keys(Key key) {
        list.push_back(key);
    };
    std::vector<Key> list;
    bool isCurrentKey() const ;
    bool isCurrentModifiers() const;
};


inline Keys operator+(const Key& left, const Key& right) {
    Keys keys;
    keys.list.push_back(left);
    keys.list.push_back(right);
    return keys;
}

inline Keys operator+(const Keys& keys, const Key& key) {
    Keys copy = keys;
    copy.list.push_back(key);
    return copy;
}

class KeyHook;

class Window {
public:
    explicit Window(std::string name) {
        m_name = name;
    }
    std::string name() {
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
    Condition(Keys keys);
    Condition(Key key) : Condition(Keys(key)) {}
    Condition(Window window);
    bool call();

private:
    std::function<bool()> m_callback;
};


class Action {
public:
    Action() {}
    Action(Key key) : Action({key}) {}
    Action(std::initializer_list<Key> keys);
//    Action(Keys keys);
    Action(std::function<void()> callback) {
        m_callback = callback;
    }
    void call(std::string path);
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
    }
    virtual ~KeyHook() {}
    bool isKey(Key key);
    Key currentKey() { return m_currentKey; };
    void start();
    bool isPressed() { return m_pressed; }
    std::string window() { return m_window; }
    void debug(Key key, bool pressed);
    std::string callPath() { return m_callPath; };
    void sendKey(Key key);
    std::set<Key> getModKeys();

    Key A = Key('a');
    Key B = Key('b');
    Key C = Key('c');
    Key D = Key('d');
    Key E = Key('e');
    Key F = Key('f');
    Key G = Key('g');
    Key H = Key('h');
    Key I = Key('i');
    Key J = Key('j');
    Key K = Key('k');
    Key L = Key('l');
    Key M = Key('m');
    Key N = Key('n');
    Key O = Key('o');
    Key P = Key('p');
    Key Q = Key('q');
    Key R = Key('r');
    Key S = Key('s');
    Key T = Key('t');
    Key U = Key('u');
    Key V = Key('v');
    Key W = Key('w');
    Key X = Key('x');
    Key Y = Key('y');
    Key Z = Key('z');
    Key Ctrl = Key(KeyCode::LCTRL);
    Key Alt = Key(KeyCode::LALT);
    Key Shift = Key(KeyCode::LSHIFT);
    Key ArrowUp = Key(KeyCode::ARROW_UP);
    Key ArrowLeft = Key(KeyCode::ARROW_LEFT);
    Key ArrowDown = Key(KeyCode::ARROW_DOWN);
    Key ArrowRight = Key(KeyCode::ARROW_RIGHT);


    //    LSHIFT = 160,
//    RSHIFT = 161,
//    LCTRL = 162,
//    RCTRL = 163,
//    LALT = 164,
//    RALT = 165

private:
    void preScript();
    std::set<Key> extractModKeys();

    void extractKey(std::set<Key>& out, Key key);
    void getKey(std::set<Key>& out, Key key);
    void sendKeyBlind(Key key, bool pressed);
    void sendKeysBlind(std::set<Key> keys, bool pressed);

    bool m_pressed;
    std::string m_window;
    bool m_handled;
    Key m_currentKey = Key(0);
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
            unTrack(path + "2");
            m_callPath += "1";
            track(then);
        } else {
            unTrack(path + "1");
            m_callPath += "2";
            track(otherwise);
        }
        m_callPath = path + "0";
    }
    void unTrack(std::string path) {
        bool pressed = m_pressed;
        m_pressed = false;
        m_actionTracker.unTrack(*this, path);
        m_pressed = pressed;
    }
    void track(Action action) {
        bool pressed = m_pressed;
        m_pressed = true;
        action.call(m_callPath);
        m_actionTracker.track(action);
        m_pressed = pressed;
    }
    void insertKeys(std::set<Key> keys);
};

}