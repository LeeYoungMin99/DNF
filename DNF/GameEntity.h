#pragma once
#include <Windows.h>

class GameEntity
{
public:
	virtual ~GameEntity() = default;

	virtual HRESULT Init() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;
};
