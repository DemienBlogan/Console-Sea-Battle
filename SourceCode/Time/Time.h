#pragma once

// Calculates time between two frames (delta time)
class Time
{
private:
	static double previousFrameTime;
	static double currentFrameTime;
	static const int MILLISEC_IN_SEC = 1000;

public:
	static double DeltaTime();
};