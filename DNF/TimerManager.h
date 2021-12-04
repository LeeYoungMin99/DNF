#pragma once
#include "Singleton.h"

class Timer;
class TimerManager : public Singleton<TimerManager>
{
public:
	virtual ~TimerManager() = default;

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	float GetDeltaTime();
private:
	Timer* timer = nullptr;
};

