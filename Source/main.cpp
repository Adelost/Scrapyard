#include "KeyHook.h"

using namespace std;
using namespace kh;

class MyKeyHook : public kh::KeyHook {
protected:
    void script() {
//        using namespace kh;
        cout << currentKey().toChar() << " " << isPressed() << endl;
//
        on(W, ArrowUp);
        on(A, ArrowLeft);
        on(S, ArrowDown);
        on(D, ArrowRight);
        on(Ctrl + W, W);
        on(Ctrl + A, A);
        on(Ctrl + S, S);
        on(Ctrl + D, D);
//s
    }
};


int main() {
    MyKeyHook hook;
    hook.start();
//    hook.debug(Key::LCTRL, true);
//    hook.debug(Key('w'), true);
//    hook.debug(Key('e'), true);
//    hook.debug(Key('e'), true);
//    hook.debug(Key('w'), false);


//    hook.debug(Key::LCTRL, false);
//    hook.debug(Key('w'), false);
//    hook.debug(Key('w'), true);
//    hook.debug(Key('w'), false);


    return 0;
}