#include "stdafx.h"
#include "Config.h"
#include "Timer.h"

void Timer::Init()
{
	timeScale = 0.0f;	
	deltaTime = 0.0f;	

	isHardware = false;	

	periodFrequency = 0;	
	currTime = 0;		
	lastTime = 0;		

	fps = 0;
	fpsFrameCount = 0;
	fpsTimeElapsed = 0.0f;

	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
	{
		isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		lastTime = currTime;
		timeScale = 1.0f / periodFrequency;
	}
	else
	{
		isHardware = false;
		currTime = timeGetTime();
		timeScale = 0.001f;
	}

	lastTime = currTime;
}

void Timer::Tick()
{
	if (isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	}
	else
	{
		currTime = timeGetTime();
	}

	deltaTime = (currTime - lastTime) * timeScale;

	++fpsFrameCount;
	fpsTimeElapsed += deltaTime;
	if (fpsTimeElapsed >= 1.0f)
	{
		fps = fpsFrameCount;
		fpsFrameCount = 0;
		fpsTimeElapsed = 0.0f;
	}

	lastTime = currTime;
}
