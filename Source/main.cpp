#include "KeyHook.h"

using namespace std;
using namespace kh;

class MyKeyHook : public kh::KeyHook {
protected:
    void script() {
        static bool enable = true;
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
        spoof(A, true);
        spoof(A, true);
        spoof(A, false);
        spoof(Ctrl, false);
    }
};


int main() {
    MyKeyHook hook;
    hook.debug();
//    hook.start();
    return 0;
}