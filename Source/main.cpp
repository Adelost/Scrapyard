#include "KeyHook.h"
#include "Utils/List.h"

using namespace std;

class MyKeyHook : public KeyHook {
protected:
    void update() {
        on([] {
            return isKey(Key::LCTRL);
        }, [] {});
    }
};

int main() {
    MyKeyHook hook;
    hook.start();
    hook.run([](Key key, Context& _) {
        on({Key('x'), Key::})
        _.on([] {
            return _.ctrl;
        }, []() {
            _.swap(Key('w'), Key('w'));
            _.swap(Key('s'), Key('s'));
            _.swap(Key('w'), Key('w'));
            _.swap(Key('w'), Key('w'));
        }, [] {
            _.swap(Key('w'), Key('w'));
            _.swap(Key('s'), Key('s'));
            _.swap(Key('w'), Key('w'));
            _.swap(Key('w'), Key('w'));
        });
    });
////        state.condition([] { return e.ctrl; })
////                .action([] {
////
////                })
////                .exit());
//
//        if (e.ctrl) {
//
//            KeyHook::swap(e, Key('a'), Key('a'));
//            KeyHook::swap(e, Key('s'), Key('s'));
//            KeyHook::swap(e, Key('d'), Key('d'));
//        } else {
//            KeyHook::swap(e, Key('w'), Key::ARROW_UP);
//            KeyHook::swap(e, Key('a'), Key::ARROW_LEFT);
//            KeyHook::swap(e, Key('s'), Key::ARROW_DOWN);
//            KeyHook::swap(e, Key('d'), Key::ARROW_RIGHT);
//        }
//
////        ae::List<Key> keys(KeyHook::getVirtualKeys());
////        ae::List<unsigned char> charKeys = keys.map<unsigned char>([](Key key) {
////            return (unsigned char) key;
////        });
//        cout << "[";
//        for (auto key: KeyHook::getVirtualKeys()) {
//            cout << (unsigned char) key << ", ";
//        }
//        cout << "]" << endl;
////        cout << "" + charKeys.toString() << endl;
//    });

    return 0;
}