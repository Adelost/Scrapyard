#include "KeyHook.h"
#include "Utils/List.h"

using namespace std;

class MyKeyHook : public KeyHook {
protected:
    void script() {
        int foo = (int) currentKey();
        cout << ((unsigned char) currentKey()) << " " << isPressed() << endl;
//        on({Key('a'), Key('s')}, Action([&] {
//        }));
        on({Key('a'), Key('s')}, Key('b'));

//        on(Key::LCTRL, Action([&] {
//            on(Key('w'), Key('w'));
//            on(Key('a'), Key('a'));
//            on(Key('s'), Key('s'));
//            on(Key('d'), Key('d'));
//        }), Action([&] {
//            on(Key('w'), Key::ARROW_UP);
//            on(Key('a'), Key::ARROW_LEFT);
//            on(Key('s'), Key::ARROW_DOWN);
//            on(Key('d'), Key::ARROW_RIGHT);
//        }));
    }
};


int main() {
    MyKeyHook hook;
    hook.debug(Key('a'), true);
    hook.debug(Key('s'), true);
    hook.debug(Key('s'), true);
    hook.debug(Key('a'), false);
    hook.debug(Key('s'), false);
//    hook.start();

    return 0;
}