#pragma once
#include <chrono>

class Timer
{
public:
	Timer();	
	float getElapsed() const;
	float Reset();
	void Stop();
	void Start();
	bool isPaused() const { return paused; }
private:
	bool paused;
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> stop;
};

//credit ChiliTomatoNoodle and Jpres
