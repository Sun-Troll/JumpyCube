#include "FrameTimer.h"

using std::chrono::steady_clock;

FrameTimer::FrameTimer()
	:
	currentTime(steady_clock::now())
{
}

float FrameTimer::FrameTime()
{
	const auto oldTime = currentTime;
	currentTime = steady_clock::now();
	std::chrono::duration<float> durationTime = currentTime - oldTime;
	return durationTime.count();
}
