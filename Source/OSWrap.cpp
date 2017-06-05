#include <iostream>
#include "OSWrap.h"

namespace kh {
std::string getActiveWindow() {
#ifdef _WIN32_
    char wnd_title[1024];
    HWND hwnd = GetForegroundWindow();
    GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
    std::string path(wnd_title);
    std::string title = path.substr(path.find_last_of("\\/") + 1, std::string::npos);
    return title;
#else
    return "";
#endif
}
Point getActiveWindowPos() {
    RECT rect;
    GetWindowRect(GetForegroundWindow(), &rect);
    return {rect.left, rect.top};
}
Point getCursorPos() {
    POINT point;
    GetCursorPos(&point);
    return {point.x, point.y};
}
Point mapToWindow(Point& globalPoint, Point& windowPos) {
    return globalPoint - windowPos;
}
Point mapToGlobal(Point& windowPoint, Point& windowPos) {
    return windowPoint + windowPos;
}
Sense::Sense() {
    m_hwnd = GetForegroundWindow();
    m_dc = GetDC(nullptr);
    m_window = getActiveWindowPos();
    auto cursorGlobal = getCursorPos();
    m_cursor = mapToWindow(cursorGlobal, m_window);
}
Sense::~Sense() {
    ReleaseDC(NULL, m_dc);
}
Color Sense::pixel(Point point) {
    std::cout << "Point: " << point.x << " " << point.y << std::endl;
    point = mapToGlobal(point, m_window);

    COLORREF color = GetPixel(m_dc, point.x, point.y);
    int r = GetRValue(color);
    int g = GetGValue(color);
    int b = GetBValue(color);
    std::cout << "Beforehex: " << r << " " << g << " " << b << std::endl;
    return {r, g, b};
}
Point Sense::window() {
    return m_window;
}
Point Sense::cursor() {
    return m_cursor;
}
}