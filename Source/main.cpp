#include "KeyHook.h"

using namespace std;
using namespace kh;

class MyKeyHook : public kh::KeyHook {
protected:
    void script() {
        std::cout << "<- " << currentKey().toStr() << " " << isPressed() << std::endl;

        on(Ctrl);
//        on(!isPressed(Ctrl), Action([&] {
//            on(W);
////            on(A);
////            on(S);
////            on(D);
////            on(isPressed(W), ArrowUp);
////            on(isPressed(A), ArrowLeft);
////            on(isPressed(S), ArrowDown);
////            on(isPressed(D), ArrowRight);
//        }));

//        on(S, D);

//        on(Q);

//        on(isPressed(Q), D);
//        on(isPressed(Ctrl), D);

//        on(Q, D);
//        on(S, F);

//        on(isPressed(Ctrl), A);
//        on(Ctrl, A);
//        on(isPressed(Ctrl), B);
//        on(Ctrl, A);
//        on(isPressed(Ctrl), B);





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
//        spoof(Ctrl, true);

//        spoof(W, true);
//        spoof(W, false);
        spoof(Ctrl, true);
        spoof(Ctrl, false);
//        spoof(W, true);
//        spoof(W, false);



//        spoof(Ctrl, true);
//        spoof(Ctrl, false);
//
//        spoof(Q, true);
//        spoof(Q, false);

//        spoof(S, true);
//        spoof(D, true);
//        spoof(D, false);
//        spoof(S, false);


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
    hook.debug();
//    hook.start();


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