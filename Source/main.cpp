#include "KeyHook.h"

using namespace std;
using namespace kh;

class MyKeyHook : public kh::KeyHook {
protected:
    void script() {

        static bool enable = true;
//        on(Q, "Here I am");
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
        send("!");
    }
public:
    void debug() {
        spoof(A, true);
//        spoof(X, true);
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