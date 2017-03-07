#include "Preincludes.h"
#include "MainWindow.h"

#include "Network.h"
#include "RenderWidget.h"

#include <Simulation/Simulation.h>
#include <Utils/StopWatch.h>
#include <Components/Time.h>
#include <Utils/Time.h>
#include <Utils/Math.h>

using namespace ae;

MainWindow::MainWindow()
{
	// Init members
	m_renderWidget = new RenderWidget(this);
	setCentralWidget(m_renderWidget);
	m_renderWidget->setMinimumSize(20, 20);
	m_loopTimer = new QTimer(this);

	// Init window
	setDockOptions(AllowNestedDocks | AllowTabbedDocks);
	setContextMenuPolicy(Qt::PreventContextMenu);
	setIconSize(QSize(20, 20));
	setTitle("Aberrant Engine");
	resize(500, 200);

	// Init game
	sys::Time.setFpsCap(60);
	m_simulation = shared_ptr<Simulation>(new Simulation);

	// Start update loop
	connect(m_loopTimer, SIGNAL(timeout()), this, SLOT(update()));
	m_loopTimer->start();
}

void MainWindow::update()
{
	m_simulation->update();
	//Time::sleep(13);
	displayFrameTime();
	adaptToFpsCap();
}

void MainWindow::displayFrameTime()
{
	float delta = sys::Time.delta();

	static float timeSinceAvg = 0.0f;
	static float timeSinceMinMax = 0.0f;
	static int fpsCount = 0;
	static float minTime = Math::MAX_FLOAT;
	static float maxTime = 0.0f;

	timeSinceAvg += delta;
	timeSinceMinMax += delta;
	fpsCount++;
	if (delta < minTime)
		minTime = delta;
	if (delta > maxTime)
		maxTime = delta;

	static float minTimeUpdate = minTime;
	static float maxTimeUpdate = maxTime;

	if (timeSinceMinMax > 1.0)
	{
		minTimeUpdate = minTime;
		maxTimeUpdate = maxTime;

		minTime = Math::MAX_FLOAT;
		maxTime = 0;
		timeSinceMinMax = 0;
	}
	if (timeSinceAvg > 0.4)
	{
		float fps = fpsCount / timeSinceAvg;
		float ms = (timeSinceAvg / fpsCount) * 1000;

		QString message = QString(" | fps %1 | ms %2 (min %3, max %4)")
		                  .arg(QString::number(fps, 'f', 1))
		                  .arg(QString::number(ms, 'f', 1))
		                  .arg(QString::number(Math::milliseconds(minTimeUpdate), 'f', 1))
		                  .arg(QString::number(Math::milliseconds(maxTimeUpdate), 'f', 1));
		setTitleMessage(message);

		timeSinceAvg = 0;
		fpsCount = 0;
	}
}

void MainWindow::adaptToFpsCap()
{
	static float delay = 0;

	float delta = Math::milliseconds(sys::Time.delta());
	float minDelta = 1000.0f / sys::Time.fpsCap();

	float correction = minDelta - delta;
	delay += correction;

	// Always apply at least 1 ms delay to allow Qt to reach its message loop.
	// This is required to prevent freeze in newer versions of Qt (such as Qt5),
	// if computation delay exceeds timer delay.
	if(delay < 1)
		delay = 1;

	m_loopTimer->setInterval(Math::round(delay));
}

void MainWindow::setTitle(QString title)
{
	m_title = title;
	setWindowTitle("Aberrant Engine");
}

void MainWindow::setTitleMessage(QString message)
{
	QString fullTitle = m_title + " " + message;
	setWindowTitle(fullTitle);
}

void MainWindow::testNetwork()
{
	Network* net = new Network(this);
	net->sayHello();
}
