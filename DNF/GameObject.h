#pragma once
#include "GameEntity.h"

class GameObject : public GameEntity
{
public:
	virtual ~GameObject() = default;

	virtual HRESULT Init() override { return S_OK; }
	virtual void Update() override {}
	virtual void Render(HDC hdc) override {}
	virtual void Release() override {}
protected:
private:

public:
protected:
	POINTFLOAT mPos = {};
private:
};
