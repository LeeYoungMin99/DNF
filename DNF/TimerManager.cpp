#include "stdafx.h"
#include "Config.h"
#include "TimerManager.h"
#include "Timer.h"

void TimerManager::Init()
{
	timer = new Timer;
	timer->Init();
}

void TimerManager::Update()
{
	timer->Tick();
}

void TimerManager::Render(HDC hdc)
{
	char szText[256] = {};
	wsprintfA((LPSTR)szText, "FPS : %d", (int)timer->GetFPS());
	TextOutA(hdc, WIN_SIZE_X - 150, 30, (LPSTR)szText, (int)strlen(szText));
}

void TimerManager::Release()
{
	SAFE_DELETE(timer);
}

float TimerManager::GetDeltaTime()
{
	if (timer) return timer->GetDeltaTime();

	return 0.0f;
}
