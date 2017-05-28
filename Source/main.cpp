#include "KeyHook.h"

using namespace std;
using namespace kh;

class MyKeyHook : public kh::KeyHook {
protected:
    void script() {
        static bool enable = true;
//        on(isWindow("Age of Empires II: HD Edition"), Action([&] {
            on(Enter - Keys::NoMute, enable);
            on(Ctrl + Enter, enable);
            on(enable, Action([&] {
//          on(, Action([&] {
                on(W, ArrowUp);
                on(A, ArrowLeft);
                on(S, ArrowDown);
                on(D, ArrowRight);
                on(Ctrl + W, W);
                on(Ctrl + A, A);
                on(Ctrl + S, S);
                on(Ctrl + D, D);
//          }));
            }));

//        }));
    }
public:
    void debug() {

//        spoof(Alt, true);
//        spoof(A, true);
        spoof(W);
//        spoof(Return);
//        spoof(W);
//        spoof(Return);
//        spoof(W);
//        spoof(Ctrl, false);
//        spoof(A, false);
//        spoof(Ctrl, false);
//        spoof(A, true);
//        spoof(A, false);
//        spoof(A, true);
//        spoof(RCtrl, true);
//        spoof(S, true);

//        spoof(S, true);
//        spoof(D, true);
//        spoof(S, false);
    }
};


int main() {
    MyKeyHook hook;
//    hook.debug();
    hook.start();
    return 0;
}