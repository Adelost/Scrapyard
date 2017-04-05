#include "KeyHook.h"

using namespace std;


int main() {
    Key k = Key(12);

    KeyHook::run([](KeyEvent& e) {
//        if (e.window != "test - Notepad++") {
//            return;
//        }

        cout << (int)e.key << endl;
        if (e.ctrl) {
//            KeyHook::sendKey((char) Key::ARROW_UP, e.pressed);

//            KeyHook::swap(e, 'a', 'd');


            KeyHook::swap(e, 'w', (unsigned char) Key::ARROW_UP);
            KeyHook::swap(e, 'a', (unsigned char) Key::ARROW_LEFT);
            KeyHook::swap(e, 's', (unsigned char) Key::ARROW_DOWN);
            KeyHook::swap(e, 'd', (unsigned char) Key::ARROW_RIGHT);
        }
    });

    return 0;
}