#pragma once


#include <unordered_map>
#include "ScanCodes.h"
#include "ScanCodes.h"
#include "Keys.h"

namespace kh {


class MouseKeyMapper {
private:
    std::unordered_map<int, ScanCode> m_codePress;
    std::unordered_map<int, ScanCode> m_codeRelease;
    std::unordered_map<ScanCode, int> m_keyPress;
    std::unordered_map<ScanCode, int> m_keyRelease;

public:
    MouseKeyMapper();
    void add(Key code, int press, int release);
    bool hasCode(int code);
    void codeToKey(int code, Key* key, bool* pressed);
    bool hasKey(Key key);
    void keyToCode(Key key, bool pressed, int* mouseCode);
};
}