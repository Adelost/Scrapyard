#include "MouseKeyMapper.h"

namespace kh {

MouseKeyMapper::MouseKeyMapper() {
    add(ScanCode::MouseLeft, 1, 2);
    add(ScanCode::MouseRight, 4, 8);
    add(ScanCode::MouseMiddle, 16, 32);
    add(ScanCode::MouseBack, 64, 128);
    add(ScanCode::MouseForward, 256, 512);
}

void MouseKeyMapper::add(Key key, int press, int release) {
    ScanCode code = key.getCode();
    m_codePress.insert({press, code});
    m_codeRelease.insert({release, code});
    m_keyPress.insert({code, press});
    m_keyRelease.insert({code, release});
}
bool MouseKeyMapper::hasCode(int code) {
    if (m_codePress.count(code)) {
        return true;
    }
    if (m_codeRelease.count(code)) {
        return true;
    }
    return false;
}
void MouseKeyMapper::codeToKey(int code, Key* key, bool* pressed) {
    if (m_codePress.count(code)) {
        *key = m_codePress[code];
        *pressed= true;
    }
    if (m_codeRelease.count(code)) {
        *key = m_codeRelease[code];
        *pressed = false;
    }
}
bool MouseKeyMapper::hasKey(Key key) {
    ScanCode code = key.getCode();
    if (m_keyPress.count(code)) {
        return true;
    }
    if (m_keyRelease.count(code)) {
        return true;
    }
    return false;
}
void MouseKeyMapper::keyToCode(Key key, bool pressed, int* mouseCode) {
    ScanCode code = key.getCode();
    if (pressed && m_keyPress.count(code)) {
        *mouseCode = m_keyPress[code];
    } else if (!pressed && m_keyRelease.count(code)) {
        *mouseCode = m_keyRelease[code];
    }
}
}