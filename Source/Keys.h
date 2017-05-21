#pragma once

#include <string>
#include <vector>
#include "ScanCodes.h"

namespace kh {

/// Holds
class Key {
public:
    Key() {
    }
    Key(ScanCode code) {
        m_code = code;
    }
    Key(std::vector<ScanCode> codes) {
        if (!codes.empty()) {
            m_code = codes[0];
        }
        m_alts = std::vector<ScanCode>(codes.begin() + 1, codes.end());
    }
    std::string toStr() const {
        return scanCodeToStr(m_code);
    }
    ScanCode getCode() const {
        return m_code;
    }
    std::vector<ScanCode> getAlts() const {
        return m_alts;
    }
    bool contains(const ScanCode& code) const {
        if(getCode() == code ){
            return true;
        }
        for (ScanCode alt : m_alts) {
            if (alt == code) {
                return true;
            }
        }
        return false;
    }
    bool operator<(const Key& right) const {
        return m_code < right.m_code;
    }
    bool operator==(const Key& right) const {
        return m_code == right.m_code;
    }

private:
    ScanCode m_code;
    std::vector<ScanCode> m_alts;
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

class KeysInherit {
public:
    Key Ctrl = Key({ScanCode::LCtrl, ScanCode::RCtrl});
    Key Alt = Key({ScanCode::LAlt, ScanCode::RAlt});
    Key Shift = Key({ScanCode::LShift, ScanCode::RShift});
    Key Win = Key({ScanCode::LWin, ScanCode::RWin});


    Key Esc = ScanCode::Esc;
    Key Num1 = ScanCode::Num1;
    Key Num2 = ScanCode::Num2;
    Key Num3 = ScanCode::Num3;
    Key Num4 = ScanCode::Num4;
    Key Num5 = ScanCode::Num5;
    Key Num6 = ScanCode::Num6;
    Key Num7 = ScanCode::Num7;
    Key Num8 = ScanCode::Num8;
    Key Num9 = ScanCode::Num9;
    Key Num0 = ScanCode::Num0;
    Key Minus = ScanCode::Minus;
    Key Plus = ScanCode::Plus;
    Key Backspace = ScanCode::Backspace;
    Key Tab = ScanCode::Tab;
    Key Q = ScanCode::Q;
    Key W = ScanCode::W;
    Key E = ScanCode::E;
    Key R = ScanCode::R;
    Key T = ScanCode::T;
    Key Y = ScanCode::Y;
    Key U = ScanCode::U;
    Key I = ScanCode::I;
    Key O = ScanCode::O;
    Key P = ScanCode::P;
    Key BracketLeft = ScanCode::BracketLeft;
    Key BracketRight = ScanCode::BracketRight;
    Key Return = ScanCode::Return;
    Key LCtrl = ScanCode::LCtrl;
    Key A = ScanCode::A;
    Key S = ScanCode::S;
    Key D = ScanCode::D;
    Key F = ScanCode::F;
    Key G = ScanCode::G;
    Key H = ScanCode::H;
    Key J = ScanCode::J;
    Key K = ScanCode::K;
    Key L = ScanCode::L;
    Key Semicolon = ScanCode::Semicolon;
    Key Quote = ScanCode::Quote;
    Key LShift = ScanCode::LShift;
    Key Backslash = ScanCode::Backslash;
    Key Z = ScanCode::Z;
    Key X = ScanCode::X;
    Key C = ScanCode::C;
    Key V = ScanCode::V;
    Key B = ScanCode::B;
    Key N = ScanCode::N;
    Key M = ScanCode::M;
    Key Colon = ScanCode::Colon;
    Key Period = ScanCode::Period;
    Key ForwardSlash = ScanCode::ForwardSlash;
    Key RShift = ScanCode::RShift;
    Key NumpadMultiply = ScanCode::NumpadMultiply;
    Key LAlt = ScanCode::LAlt;
    Key Space = ScanCode::Space;
    Key CapsLock = ScanCode::CapsLock;
    Key NumLock = ScanCode::NumLock;
    Key ScrollLock = ScanCode::ScrollLock;
    Key Numpad7 = ScanCode::Numpad7;
    Key Numpad8 = ScanCode::Numpad8;
    Key Numpad9 = ScanCode::Numpad9;
    Key NumpadMinus = ScanCode::NumpadMinus;
    Key Numpad4 = ScanCode::Numpad4;
    Key Numpad5 = ScanCode::Numpad5;
    Key Numpad6 = ScanCode::Numpad6;
    Key NumpadPlus = ScanCode::NumpadPlus;
    Key Numpad1 = ScanCode::Numpad1;
    Key Numpad2 = ScanCode::Numpad2;
    Key Numpad3 = ScanCode::Numpad3;
    Key Numpad0 = ScanCode::Numpad0;
    Key NumpadDecimalPoint = ScanCode::NumpadDecimalPoint;
    Key Enter = ScanCode::Enter;
    Key RCtrl = ScanCode::RCtrl;
    Key PrintScreen = ScanCode::PrintScreen;
    Key NumpadDivide = ScanCode::NumpadDivide;
    Key RAlt = ScanCode::RAlt;
    Key Home = ScanCode::Home;
    Key ArrowUp = ScanCode::ArrowUp;
    Key PageUp = ScanCode::PageUp;
    Key ArrowLeft = ScanCode::ArrowLeft;
    Key ArrowRight = ScanCode::ArrowRight;
    Key End = ScanCode::End;
    Key ArrowDown = ScanCode::ArrowDown;
    Key PageDown = ScanCode::PageDown;
    Key Insert = ScanCode::Insert;
    Key Delete = ScanCode::Delete;
    Key LWin = ScanCode::LWin;
    Key RWin = ScanCode::RWin;
    Key Menu = ScanCode::Menu;
};
}