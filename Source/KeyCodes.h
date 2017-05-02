#pragma once

#include <string>

namespace kh {

class Key {
public:
    Key() : Key(0) {
    }
    Key(int code) {
        m_code = code;
        m_str = toStr();
    }
    std::string toStr() const {
        int c = m_code;
        return c == 16 ? "Q" :
               c == 17 ? "W" :
               c == 18 ? "E" :
               c == 19 ? "R" :
               c == 20 ? "T" :
               c == 21 ? "Y" :
               c == 22 ? "U" :
               c == 23 ? "I" :
               c == 24 ? "O" :
               c == 25 ? "P" :

               c == 30 ? "A" :
               c == 31 ? "S" :
               c == 32 ? "D" :
               c == 33 ? "F" :
               c == 34 ? "G" :
               c == 35 ? "H" :
               c == 36 ? "J" :
               c == 37 ? "K" :
               c == 38 ? "L" :

               c == 44 ? "Z" :
               c == 45 ? "X" :
               c == 46 ? "C" :
               c == 47 ? "V" :
               c == 48 ? "B" :
               c == 49 ? "N" :
               c == 50 ? "M" :

               c == 1 ? "Escape" :
               c == 42 ? "Shift" :
               c == 29 ? "Ctrl" :
               c == 56 ? "Alt" :
               c == 54 ? "RShift" :
               c == 157 ? "RCtrl" :
               c == 184 ? "RAlt" :

               c == 200 ? "Up" :
               c == 203 ? "Left" :
               c == 208 ? "Down" :
               c == 205 ? "Right" :

               c == 156 ? "Enter" :
               c == 28 ? "Return" :

               std::to_string(c);
    }
    int getCode() const {
        return m_code;
    }
    bool operator<(const Key& right) const {
        return m_code < right.m_code;
    }
    bool operator==(const Key& right) const {
        return m_code == right.m_code;
    }
private:
    int m_code;
    std::string m_str;
};

class Keys {
public:
    Keys() {};
    Keys(Key key) {
        list.push_back(key);
    };
    std::vector<Key> list;
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

class KeyCodes {
public:
    Key Esc = 1;

    Key Num1 = 2;
    Key Num2 = 3;
    Key Num3 = 4;
    Key Num4 = 5;
    Key Num5 = 6;
    Key Num6 = 7;
    Key Num7 = 8;
    Key Num8 = 9;
    Key Num9 = 10;
    Key Num0 = 11;

    Key Q = 16;
    Key W = 17;
    Key E = 18;
    Key R = 19;
    Key T = 20;
    Key Y = 21;
    Key U = 22;
    Key I = 23;
    Key O = 24;
    Key P = 25;

    Key A = 30;
    Key S = 31;
    Key D = 32;
    Key F = 33;
    Key G = 34;
    Key H = 35;
    Key J = 36;
    Key K = 37;
    Key L = 38;

    Key Z = 44;
    Key X = 45;
    Key C = 46;
    Key V = 47;
    Key B = 48;
    Key N = 49;
    Key M = 50;

    Key Tab = 15;
    Key CapsLock = 58;
    Key Backspace = 14;
    Key Return = 28;

    Key Shift = 42;
    Key Ctrl = 29;
    Key Alt = 56;
    Key RShift = 54;
    Key RCtrl = 157;
    Key RAlt = 184;

    Key Up = 200;
    Key Left = 203;
    Key Down = 208;
    Key Right = 205;

    Key Numpad1 = 79;
    Key Numpad2 = 80;
    Key Numpad3 = 81;
    Key Numpad4 = 75;
    Key Numpad5 = 76;
    Key Numpad6 = 77;
    Key Numpad7 = 71;
    Key Numpad8 = 72;
    Key Numpad9 = 73;
    Key Enter = 156;
};

}