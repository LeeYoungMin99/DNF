#pragma once
#include "GameEntity.h"

// �츮�� ������ ���� ����
class BmpImage;
class MainGame : public GameEntity
{
private:
	BmpImage* mpBackBuffer = nullptr;
public:
	virtual ~MainGame() {}

	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};