#include "Preincludes.h"
#include "RenderWidget.h"

#include <GraphicsEngine/GraphicsEngine.h>


#include <Utils/DebugOnly.h>

RenderWidget::RenderWidget(QWidget* parent) : QWidget(parent)
{
	// Window settings
	setAttribute(Qt::WA_OpaquePaintEvent); // Needed to render to widget
	setAttribute(Qt::WA_PaintOnScreen); // Needed to render to widget
	setMouseTracking(true);

	// Init renderer
	GraphicsEngine::setWindowHandle((HWND)winId());
}

RenderWidget::~RenderWidget()
{
}

QPaintEngine* RenderWidget::paintEngine() const
{
	return nullptr;
}
