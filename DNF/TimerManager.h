#pragma once
#include "Singleton.h"

class Timer;
class TimerManager : public Singleton<TimerManager>
{
private:
	Timer* timer = nullptr;

public:
	virtual ~TimerManager() = default;

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	float GetDeltaTime();
};

