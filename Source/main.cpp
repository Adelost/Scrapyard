#include "KeyHook.h"

using namespace std;
using namespace kh;

class MyKeyHook : public kh::KeyHook {
protected:
    void script() {
        std::cout << "<- " << currentKey().toStr() << " " << isPressed() << std::endl;

//        mute(Ctrl);
//        on(!isPressed(Ctrl), Action([&] {
////            silence({W, A, S, D});
//            on(W, Up);
//            on(A, Left);
//            on(S, Down);
//            on(D, Right);
//        }));
        on(A, B);
//        on(A, Left);
//        on(S, wDown);
//        on(D, Right);
//
//        on(Ctrl + W, W);
//        on(Ctrl + A, A);
//        on(Ctrl + S, S);
//        on(Ctrl + D, D);




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





//        on(T, Up);
//        on(F, Left);
//        on(G, Down);
//        on(H, Right);
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
        spoof(Shift, true);
        spoof(A, true);
//        spoof(W, false);
//        spoof(W, true);
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


//        spoof(Down, true);
//        spoof(Right, true);
//        spoof(Down, false);
//        spoof(Right, false);
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