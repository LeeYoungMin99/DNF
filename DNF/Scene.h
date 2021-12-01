#pragma once
#include "GameEntity.h"

class Scene : public GameEntity
{
public:
	virtual ~Scene() = default;
	virtual HRESULT Init() override = 0;
	virtual void Update() override = 0;
	virtual void Render(HDC hdc) override = 0;
	virtual void Release() override = 0;
};
