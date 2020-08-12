#include "Timer.h"

using namespace std::chrono;

/*Timer::Timer()
{
	last = steady_clock::now();
}

float Timer::Reset() 
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float Timer::getElapsed() const 
{
	return duration<float>(steady_clock::now() - last).count();
}*/

Timer::Timer()
	: paused(false)
{
	start = high_resolution_clock::now();
	stop = high_resolution_clock::now();
}

float Timer::getElapsed() const
{
	if (!paused)
		return (duration<float>(high_resolution_clock::now() - start)).count();
	else
		return (duration<float>(stop - start)).count();
}

void Timer::Stop()
{
	if (paused == true)
		return;
	this->paused = true;
	stop = high_resolution_clock::now();
}

void Timer::Start()
{
	if (!paused)
		return;
	this->paused = false;
	start = high_resolution_clock::now();
}

float Timer::Reset()
{
	this->paused = false;
	start = high_resolution_clock::now();
	const duration<float> dur = start - stop;
	return dur.count();
}
