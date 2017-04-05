#pragma once

#include <iostream>
#include <functional>
#include <set>

struct KeyEvent {
    unsigned char key;
    bool pressed;
    bool ctrl;
    bool shift;
    bool alt;
    bool handled;
    std::string window;
};

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

class KeyHook {
public:
    static void run(std::function<void (KeyEvent&)> callback);
    static std::string getActiveWindowTitle();
    static void sendKey(unsigned char key, bool pressed);
    static void swap(KeyEvent& event, unsigned char from, unsigned char to);
    static bool isPressed(Key key);
    static std::set<unsigned char> unsetModKeys();
    static void extractIfPressed(std::set<unsigned char>& out, Key key);
    static void setKeys(const std::set<unsigned char>& keys);
    static void sendKeyBlind(unsigned char key, bool pressed);
    static void sendKeysBlind(std::set<unsigned char> keys, bool pressed);
};

