#include "Timer.h"

using namespace std::chrono;

Timer::Timer()
	: paused(false)
{
	start = high_resolution_clock::now();
	stop = high_resolution_clock::now();
}

float Timer::getElapsed() const
{
	return (!paused) ? 
		(duration<float>(high_resolution_clock::now() - start)).count()
		: (duration<float>(stop - start)).count();
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
