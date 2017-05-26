#include "KeyHook.h"

using namespace std;
using namespace kh;

class MyKeyHook : public kh::KeyHook {
protected:
    void script() {
        static bool enable = true;
//        on(isPressed(Return), enable);
//        on(Ctrl + Return, enable);
//        on(enable, Action([&] {
////          on(isWindow("Age of Empires II: HD Edition"), Action([&] {
//            on(W, ArrowUp);
//            on(A, ArrowLeft);
//            on(S, ArrowDown);
//            on(D, ArrowRight);
//            on(Ctrl + W, W);
//            on(Ctrl + A, A);
//            on(Ctrl + S, S);
//            on(Ctrl + D, D);
////          }));
//        }));


        on(Ctrl + Alt + A, Num1);
//        on(Ctrl + Shift + A, Num2);
//        on(Ctrl + Shift + Alt + A, Num3);
//        on(Ctrl + Alt + A, Num4);
//        on(Shift + Alt + A, Num5);
//        on(2);


//        on(Ctrl + S, Q);
//        on(W, std::string("World is that it."));
//        on(enable, Action([&] {
//            on(W, ArrowUp);
//            on(A, ArrowLeft);
//            on(S, ArrowDown);
//            on(D, ArrowRight);
//            on(LCtrl + W, W);
//            on(LCtrl + A, A);
//            on(LCtrl + S, S);
//            on(LCtrl + D, D);
//        }));
//        send("!");
    }
public:
    void debug() {
        spoof(Ctrl, true);
        spoof(Alt, true);
        spoof(A, true);
//        spoof(A, true);
//        spoof(A, false);
//        spoof(LCtrl, false);
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
    hook.debug();
//    hook.start();
    return 0;
}