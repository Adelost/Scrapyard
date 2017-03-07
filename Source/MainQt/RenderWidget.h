#pragma once

#include "Preforwards.h"
#include <QWidget>

class RenderWidget : public QWidget
{
	Q_OBJECT

public:
	RenderWidget(QWidget* p_parent);
	~RenderWidget();

	// Overrides Qt:s own paint engine. Prevents flicker.
	QPaintEngine* paintEngine() const;

protected:
	// Should not be implemented
	void paintEvent(QPaintEvent* p_event) {}

private:
};