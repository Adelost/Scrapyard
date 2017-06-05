#include "KeyHook.h"
#include "OSWrap.h"


using namespace std;
using namespace kh;

class MyKeyHook : public kh::KeyHook {
protected:
    void script() {
        Sense sense;
//        Color c = getPixel(cursorPos());
        std::cout << "Window: " << currentWindow() << std::endl;

        std::cout << "Color: " << sense.pixel(sense.cursor()).toHex() << std::endl;

//        HDC dc = GetDC(NULL);
//        COLORREF color = GetPixel(dc, 0, 0);
//        ReleaseDC(NULL, dc);
//        int red = GetRValue(color);
//        int green = GetGValue(color);
//        int blue = GetBValue(color);


//        static bool enable = true;
////        on(isWindow("Age of Empires II: HD Edition"), Action([&] {
//            on(Enter - Keys::NoMute, enable);
//            on(Ctrl + Enter, enable);
//            on(enable, Action([&] {
////          on(, Action([&] {
//                on(W, ArrowUp);
//                on(A, ArrowLeft);
//                on(S, ArrowDown);
//                on(D, ArrowRight);
//                on(Ctrl + W, W);
//                on(Ctrl + A, A);
//                on(Ctrl + S, S);
//                on(Ctrl + D, D);
////          }));
//            }));

//        }));
    }
    void init(){
        every(1000, []{
            std::cout << "task1 says: "  << std::endl;
        });

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