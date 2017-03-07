#pragma once

#include "Preforwards.h"
#include <QMainWindow.h>

class Simulation;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

	void setTitle(QString title);
	void setTitleMessage(QString message);

public slots:
	void update();

private:
	void displayFrameTime();
	void testNetwork();
	void adaptToFpsCap();

	QString m_title;
	QTimer* m_loopTimer;
	QWidget* m_renderWidget;
	shared_ptr<Simulation> m_simulation;
};

