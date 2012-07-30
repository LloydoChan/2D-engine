//Timer.cpp
#include "Timer.h"

namespace Advanced2D
{
	Timer::Timer()
	{
		timerStart = timeGetTime();
		Reset();
	}

	Timer::~Timer()
	{
	}

	DWORD Timer::GetTimer()
	{
		return (DWORD)(timeGetTime());
	}

	void Timer::Sleep(int ms)
	{
		DWORD start = GetTimer();
		while(start + ms > GetTimer());
	}

	void Timer::Reset()
	{
		stopWatchStart = GetTimer();
	}

	bool Timer::StopWatch(int ms)
	{
		if(timeGetTime() > stopWatchStart + ms)
		{
			stopWatchStart = GetTimer();
			return true;
		}

		else
			return false;
	}
};