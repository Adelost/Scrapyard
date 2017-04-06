#include "KeyHook.h"
#include "Utils/List.h"

using namespace std;


int main() {
    auto lam = [&] { return 42; };
    int foo = lam();

    KeyHook::run([](KeyEvent& e) {
        state.condition([]() { return e.ctrl; })
                .action([] {})
                .exit());

        if (e.ctrl) {
            KeyHook::swap(e, Key('w'), Key('w'));
            KeyHook::swap(e, Key('a'), Key('a'));
            KeyHook::swap(e, Key('s'), Key('s'));
            KeyHook::swap(e, Key('d'), Key('d'));
        } else {
            KeyHook::swap(e, Key('w'), Key::ARROW_UP);
            KeyHook::swap(e, Key('a'), Key::ARROW_LEFT);
            KeyHook::swap(e, Key('s'), Key::ARROW_DOWN);
            KeyHook::swap(e, Key('d'), Key::ARROW_RIGHT);
        }

//        ae::List<Key> keys(KeyHook::getVirtualKeys());
//        ae::List<unsigned char> charKeys = keys.map<unsigned char>([](Key key) {
//            return (unsigned char) key;
//        });
        cout << "[";
        for (auto key: KeyHook::getVirtualKeys()) {
            cout << (unsigned char) key << ", ";
        }
        cout << "]" << endl;
//        cout << "" + charKeys.toString() << endl;
    });

    return 0;
}