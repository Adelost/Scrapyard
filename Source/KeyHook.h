#pragma once

#include <iostream>
#include <functional>
#include <set>

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

class Context {
public:
    Context(KeyHook hook) {
        m_hook = hook;
    }
    bool pressed;
    bool ctrl;
    bool shift;
    bool alt;
    bool handled;
    std::string window;

    std::string callpath;

    bool key(Key key) { m_hook.isPressed(key) };

    void condition(std::function<void(Context&)> callback, std::function<void(bool on)> action) {

    }
private:
    KeyHook m_hook;

};

class Action {
public:
    void action(std::function<void(bool on)> action) {

    }
};


class KeyHook {
public:
    void run(std::function<void(Context&)> callback);
    static std::string getActiveWindowTitle();
    static void sendKey(Key key, bool pressed);
    static void swap(Key event, Key from);
    static bool isPressed(Key key);
    static std::set<Key> unsetModKeys();
    static void extractIfPressed(std::set<Key>& out, Key key);
    static void setKeys(const std::set<Key>& keys);
    static void sendKeyBlind(Key key, bool pressed);
    static void sendKeysBlind(std::set<Key> keys, bool pressed);
    static std::set<Key> getVirtualKeys();
};

