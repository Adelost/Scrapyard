#include "KeyHook.h"

#include "thread"

using namespace std;
using namespace kh;

class MyKeyHook : public kh::KeyHook {
protected:
    void script() {
        static bool enable = true;
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
//        every(100, [&] {
//            std::cout << sense.pixel(sense.cursor()).toHex() << std::endl;
////            send(Q);
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




//    FARPROC pGetPixel;
//    HINSTANCE _hGDI = LoadLibrary("gdi32.dll");
//    if(_hGDI)
//    {
//        pGetPixel = GetProcAddress(_hGDI, "GetPixel");
//        HDC _hdc = GetDC(NULL);
//        if(_hdc)
//        {
//            POINT _cursor;
//            GetCursorPos(&_cursor);
//            COLORREF _color = (*pGetPixel) (_hdc, _cursor.x, _cursor.y);
//            int _red = GetRValue(_color);
//            int _green = GetGValue(_color);
//            int _blue = GetBValue(_color);
//
//            printf("Red: 0x%02x\n", _red);
//            printf("Green: 0x%02x\n", _green);
//            printf("Blue: 0x%02x\n", _blue);
//        }
//        FreeLibrary(_hGDI);

    return 0;
}
