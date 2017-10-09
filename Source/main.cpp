#include "KeyHook.h"

#include "thread"

using namespace std;
using namespace kh;

class MyKeyHook : public kh::KeyHook {
protected:
    void script() {
        static bool enable = true;
        on(MouseScrollDown, ArrowDown);
        on(MouseScrollUp, ArrowUp);
        on(MouseTiltLeft, ArrowLeft);
        on(MouseTiltRight, ArrowRight);

        on(ArrowDown, MouseScrollDown);
        on(ArrowUp, MouseScrollUp);
        on(ArrowLeft, MouseTiltLeft);
        on(ArrowRight, MouseTiltRight);



        on(isWindow("Company Of Heroes 2"), Action([&] {
            on(Enter - Keys::NoMute, enable);
            on(Ctrl + Enter, enable);
            on(enable, Action([&] {
                on(W, ArrowUp);
                on(A, ArrowLeft);
                on(S, ArrowDown);
                on(D, ArrowRight);
                on(Ctrl + W, W);
                on(Ctrl + A, A);
                on(Ctrl + S, S);
                on(Ctrl + D, D);
            }));
        }));
    }
    void init() {
//        every(1000, [&] {
//            std::cout << sense.pixel(sense.cursor()).toHex() << std::endl;
//            send(Q);
//        });
    }
public:
    void debug() {
        spoof(MouseForward, true);
//        spoof(A, true);
//        spoof(W);
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


//    std::thread t1(foo);
//    t1.join();

    return 0;
}
