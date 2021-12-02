#pragma once
#include "GameObject.h"

class Character : public GameObject
{
public:

	virtual ~Character() = default;

	virtual HRESULT Init() override { return S_OK; }
	virtual void Update() override {}
	virtual void Render(HDC hdc) override {}
	virtual void Release() override {}

protected:
	eMoveDir mDir = eMoveDir::None;
	float mMoveSpeed = 0.0f;
};

