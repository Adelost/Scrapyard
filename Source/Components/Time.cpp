#include "Time.h"

//extern int sys::Fooled;

namespace sys
{
	TimeSystem Time;

	void TimeSystem::update()
	{
		// Calculate raw delta time
		m_rawDelta = deltaTimer.time();
		deltaTimer.start();

		_calcDeltaTime();
	}
}
