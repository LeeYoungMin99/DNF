#pragma once

#include "GameEntity.h"

class GameObject;
class Component : public GameEntity
{
public:
	Component(GameObject* owner, INT32 order = 100) noexcept;
	virtual ~Component() noexcept;

	INT32 GetOrder() const noexcept;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

protected:
	GameObject* mOwner = nullptr;

private:
	INT32 mOrder = 100;
};

