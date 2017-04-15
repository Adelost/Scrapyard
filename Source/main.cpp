#include "KeyHook.h"

using namespace std;
using namespace kh;

class MyKeyHook : public kh::KeyHook {
protected:
    void script() {
//        using namespace kh;
//        if(currentKey() == A)
//        {
//            sendKeyBlind(ArrowLeft, true);
//        }
//        cout << currentWindow() << endl;
//        cout << currentKey().toChar() << " " << isPressed() << endl;
//sssssssssssssssssssssssssssssssssssssssasasas


//        on(Window("Company Of Heroes 2"), Action([&] {
        on(T, ArrowUp);
        on(F, ArrowLeft);
        on(G, ArrowDown);
        on(H, ArrowRight);

        on(I, W);
        on(J, A);
        on(K, S);
        on(L, D);
//        on(Ctrl + W, W);
//        on(Ctrl + A, A);s
//        on(Ctrl + S, S);a
//        on(Ctrl + D, D);
//        }));
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