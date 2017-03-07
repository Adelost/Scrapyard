#include "GraphicsEngine.h"

HWND GraphicsEngine::m_windowHandle;

GraphicsEngine::GraphicsEngine()
{
	std::cout << "Foo, woe is me" << std::endl;
}

void GraphicsEngine::setWindowHandle(HWND windowHandle)
{
	m_windowHandle = windowHandle;
}
