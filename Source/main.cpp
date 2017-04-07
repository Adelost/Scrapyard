#include "KeyHook.h"
#include "Utils/List.h"

using namespace std;

class MyKeyHook : public KeyHook {
protected:
    void script() {
        on(Key::LCTRL, Action([&] {
            on(Key('w'), Key('w'));
            on(Key('a'), Key('a'));
            on(Key('s'), Key('s'));
            on(Key('d'), Key('d'));
        }), Action([&] {
            on(Key('w'), Key::ARROW_UP);
            on(Key('a'), Key::ARROW_LEFT);
            on(Key('s'), Key::ARROW_DOWN);
            on(Key('d'), Key::ARROW_RIGHT);
            on(Condition([] { return true; }), Key::LCTRL);

        }));
    }
};


int main() {
    MyKeyHook hook;
    hook.start();
    return 0;
}
