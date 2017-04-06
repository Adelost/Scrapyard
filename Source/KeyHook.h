#pragma once

#include <iostream>
#include <functional>
#include <set>
#include <initializer_list>

enum class Key {
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

class Condition {
public:
    Condition() {
        m_callback = [] { return true; };
    }
    Condition(std::function<bool()> callback) {
        m_callback = callback;
    }
    Condition(std::initializer_list<Key> keys) {
        m_keys = keys;
    }
    Condition(Key key) {
        m_keys = {key};
    }
    bool call(KeyHook& hook);
private:
    std::function<bool()> m_callback;
    std::initializer_list<Key> m_keys;
};

class Action {
public:
    Action() {

    }
    Action(std::function<void()> callback) {
        m_callback = callback;
    }
//    Action(void (* callback)()) {
//        m_callback = callback;
//    }
    Action(std::initializer_list<Key> keys) {
        m_keys = keys;
    }
    Action(Key key) {
        m_keys = {key};
    }
    void call(KeyHook& hook);
private:
    std::function<void()> m_callback;
    std::initializer_list<Key> m_keys;
};


class KeyHook {
private:
    std::string getActiveWindowTitle();
    void sendKey(Key key, bool pressed);
    void swap(Key event, Key from) {};

    std::set<Key> unsetModKeys();
    void extractIfPressed(std::set<Key>& out, Key key);
    void setKeys(const std::set<Key>& keys);
    void sendKeyBlind(Key key, bool pressed);
    void sendKeysBlind(std::set<Key> keys, bool pressed);
    std::set<Key> getVirtualKeys();

protected:
    virtual void update() = 0;
    void on(Condition given, Action then, Action otherwise = Action()) {
    }

public:
    virtual ~KeyHook() {}
    bool isKey(Key key);
    void start() {

    };

protected:

};

