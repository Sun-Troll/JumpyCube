#pragma once
#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float FrameTime();
private:
	std::chrono::steady_clock::time_point currentTime;
};