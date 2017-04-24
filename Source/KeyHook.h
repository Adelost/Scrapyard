#pragma once

#include <iostream>
#include <functional>
#include <set>
#include <vector>
#include <initializer_list>
#include "KeyCodes.h"

namespace kh {

class Keys {
public:
    Keys() {};
    Keys(Key key) {
        list.push_back(key);
    };
    std::vector<Key> list;
    bool isCurrentKey() const;
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
        m_callback = [] { return 1; };
    }
    Condition(bool active) {
        m_callback = [=]() {
            return active;
        };
    }
    Condition(std::function<int()> callback) {
        m_callback = callback;
    }
    Condition(std::function<bool()> callback) {
        m_callback = [=]() {
            return callback() ? 1 : 0;
        };
    }
    Condition(Keys keys);
    Condition(Key key) : Condition(Keys(key)) {}
    Condition(Window window);
    int call();

private:
    std::function<int()> m_callback;
};


class Action {
public:
    Action() {}
    Action(Key key) : Action(Keys(key)) {}
    Action(Keys keys);
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

class KeyHook : public KeyCodes {
public:
    KeyHook() {
    }
    virtual ~KeyHook() {}
    bool isPressed(Key key);
    Key currentKey() { return m_currentKey; };
    void start();
    bool isPressed() { return m_pressed; }
    std::string currentWindow() { return m_window; }
    virtual void debug() = 0;
    virtual void spoof(Key key, bool pressed);

    std::string callPath() { return m_callPath; };
    void sendKey(Key key);
    std::set<Key> getModKeys();

    void sendKeyBlind(Key key, bool pressed);

private:
    void preScript();
    std::set<Key> extractModKeys();

    void extractKey(std::set<Key>& out, Key key);
    void getKey(std::set<Key>& out, Key key);
    void sendKeysBlind(std::set<Key> keys, bool pressed);

    bool m_pressed;
    std::string m_window;
    bool m_intercepted;
    bool m_injected = false;
    Key m_currentKey = Key(0);
    std::string m_callPath = "";
    std::set<Key> m_hardwareKeys;
    ActionTracker m_actionTracker;
    bool m_debug = false;


protected:
    virtual void script() = 0;

    void on(Condition given, Action then, Action otherwise = Action()) {
        std::string path = m_callPath;
        int callCode = given.call();
        if (callCode == 1) {
            unTrack(path + "2");
            m_callPath += "1";
            track(then);
        } else if (callCode == 0) {
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