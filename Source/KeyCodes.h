#pragma once

#include <string>

namespace kh {

class Key {
public:
    Key() {
    }
    Key(int code) {
        m_code = code;
    }
    std::string toStr() const {
        int code = m_code;
        if (code == 16) return "Q";
        if (code == 17) return "W";
        if (code == 18) return "E";
        if (code == 19) return "R";
        if (code == 20) return "T";
        if (code == 21) return "Y";
        if (code == 22) return "U";
        if (code == 23) return "I";
        if (code == 24) return "O";
        if (code == 25) return "P";

        if (code == 30) return "A";
        if (code == 31) return "S";
        if (code == 32) return "D";
        if (code == 33) return "F";
        if (code == 34) return "G";
        if (code == 35) return "H";
        if (code == 36) return "J";
        if (code == 37) return "K";
        if (code == 38) return "L";

        if (code == 44) return "Z";
        if (code == 45) return "X";
        if (code == 46) return "C";
        if (code == 47) return "V";
        if (code == 48) return "B";
        if (code == 49) return "N";
        if (code == 50) return "M";

        if (code == 42) return "Shift";
        if (code == 29) return "Ctrl";
        if (code == 56) return "Alt";
        if (code == 54) return "RShift";
        if (code == 157) return "RCtrl";
        if (code == 184) return "RAlt";

        if (code == 200) return "Up";
        if (code == 203) return "Left";
        if (code == 208) return "Down";
        if (code == 205) return "Right";

        if (code == 156) return "Enter";
        if (code == 28) return "Return";

        return std::to_string(code);
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
};

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

    Key ArrowUp = 200;
    Key ArrowLeft = 203;
    Key ArrowDown = 208;
    Key ArrowRight = 205;

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