#pragma once
#include "GameEntity.h"

// 우리가 구성할 게임 월드
class BmpImage;
class MainGame : public GameEntity
{
private:
	BmpImage* backBuffer = nullptr;
public:
	virtual ~MainGame() {}

	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};