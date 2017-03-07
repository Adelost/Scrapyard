#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>

class GraphicsEngine
{
public:
	GraphicsEngine();

	void clearRenderTargets();
	void renderMesh(int meshId);

	void setRasterizerStateSettings();
	void setPrimitiveTopology();

	static void setWindowHandle(HWND windowHandle);

private:
	static HWND m_windowHandle;
};