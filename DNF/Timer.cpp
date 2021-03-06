#include "stdafx.h"

#include "Timer.h"

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point Timer::_prevTime = {};
float Timer::_deltaTime = 0.0f;
float Timer::_timeScale = 1.0f;

void Timer::SetTimeScale(float timeScale)
{
	_timeScale = timeScale;
}

float Timer::GetTimeScale() 
{
	return _timeScale;
}

float Timer::GetDeltaTime() 
{
	return _deltaTime * _timeScale;
}

void Timer::Init() 
{
	_prevTime = high_resolution_clock::now();
}

bool Timer::CanUpdate() 
{
	auto current = high_resolution_clock::now();

	duration<float> elapsed = current - _prevTime;

	if (MS_PER_UPDATE * 0.001f > elapsed.count())
	{
		return false;
	}

	_deltaTime = elapsed.count();

	_prevTime = current;

	return true;
}