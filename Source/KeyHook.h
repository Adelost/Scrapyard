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

struct KeyEvent {
    Key key;
    bool pressed;
    bool ctrl;
    bool shift;
    bool alt;
    bool handled;
    std::string window;
    bool isPressed(Key key1);
    std::string callpath;
};


class KeyHook {
public:
    static void run(std::function<void(KeyEvent&)> callback);
    static std::string getActiveWindowTitle();
    static void sendKey(Key key, bool pressed);
    static void swap(KeyEvent& event, Key from, Key to);
    static bool isPressed(Key key);
    static std::set<Key> unsetModKeys();
    static void extractIfPressed(std::set<Key>& out, Key key);
    static void setKeys(const std::set<Key>& keys);
    static void sendKeyBlind(Key key, bool pressed);
    static void sendKeysBlind(std::set<Key> keys, bool pressed);
    static std::set<Key> getVirtualKeys();
};

