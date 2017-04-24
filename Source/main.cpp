#include "KeyHook.h"

using namespace std;
using namespace kh;

class MyKeyHook : public kh::KeyHook {
protected:
    void script() {
//        std::cout << "<- " << currentKey().toStr() << " " << isPressed() << std::endl;

//        on(isPressed(Ctrl), Action([&] {
//
////            on(isPressed(W), Action([&] { sendKey(ArrowUp); }));
////            on(isPressed(A), ArrowLeft);
////            on(isPressed(S), ArrowDown);
////            on(isPressed(D), ArrowRight);
//        }));

        on(Q, A);
        on(Q, B);





//        on(T, ArrowUp);
//        on(F, ArrowLeft);
//        on(G, ArrowDown);
//        on(H, ArrowRight);
//
//        on(Ctrl + W, W);
//        on(Ctrl + A, A);
//        on(Ctrl + S, S);
//        on(Ctrl + D, D);
    }
public:
    void debug() {
        spoof(Ctrl, true);
        spoof(Ctrl, false);
        spoof(Ctrl, true);
        spoof(Ctrl, false);
//        spoof(ArrowDown, true);
//        spoof(ArrowRight, true);
//        spoof(ArrowDown, false);
//        spoof(ArrowRight, false);
//
//        spoof(S, true);
//        spoof(D, true);
//        spoof(S, false);
//        spoof(D, false);
    }

};


int main() {
    MyKeyHook hook;
    hook.start();
//    hook.debug();
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