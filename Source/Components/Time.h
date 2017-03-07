#pragma once

#include <Utils/StopWatch.h>

namespace sys
{
class TimeSystem
{
public:
	TimeSystem()
	{
		m_delta = 0.0f;
		m_rawDelta = 0.0f;
		m_timeScale = 1.0f;
		m_maxAllowedDelta = 0.25f;
		m_fpsCap = 360;
	}

	//! Calculates time for the next frame. Should only be called once per
	//! frame at the start of the frame.
	void update();

	void start()
	{
		deltaTimer.start();
	}

	void pause()
	{
		deltaTimer.pause();
	}

	void resume()
	{
		deltaTimer.resume();
	}

	//! Returns the time in seconds between previous frame and this frame.
	float delta()
	{
		return m_delta;
	}

	//! Returns delta time without any modifications.
	float rawDelta()
	{
		return m_rawDelta;
	}

	//! Sets maximum allowed time delta between frames. This assures
	//! consistency during low frame-rates.
	void setMaxAllowedDelta(float delta)
	{
		m_maxAllowedDelta = delta;
	}

	int fpsCap()
	{
		return m_fpsCap;
	}

	//! Caps frame rate to specified frames per second.
	void setFpsCap(int fps)
	{
		m_fpsCap = fps;
	}

	//! The scale at which time is passing. Useful for slow motion effects.
	void setTimeScale(float scale)
	{
		m_timeScale = scale;
		_calcDeltaTime();
	}

private:
	void _calcDeltaTime()
	{
		// Calculate delta time
		float delta = m_rawDelta > m_maxAllowedDelta ? m_maxAllowedDelta : m_rawDelta;
		m_delta = delta * m_timeScale;
	}

	float m_delta;
	float m_rawDelta;
	float m_timeScale;
	float m_maxAllowedDelta;
	int m_fpsCap;
	ae::StopWatch deltaTimer;
};
extern sys::TimeSystem Time;
}
