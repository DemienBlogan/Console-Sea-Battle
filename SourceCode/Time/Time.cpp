#include "Time.h"

#include <ctime>

double Time::previousFrameTime = 0;
double Time::currentFrameTime = std::clock();

double Time::DeltaTime()
{
	previousFrameTime = currentFrameTime;
	currentFrameTime = std::clock();
	return (currentFrameTime - previousFrameTime) / MILLISEC_IN_SEC;
}