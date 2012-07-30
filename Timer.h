//Timer.h
#pragma once 
#include <time.h>
#include <Windows.h>
namespace Advanced2D
{
	class Timer
	{
		public:
			Timer();
			~Timer();
			DWORD GetTimer();
			DWORD GetStartTimeMillis();
			void Sleep(int ms);
			void Reset();
			bool StopWatch(int ms);
		private:
			DWORD timerStart;
			DWORD stopWatchStart;
	};
};