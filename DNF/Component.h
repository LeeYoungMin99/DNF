#pragma once

#include "GameEntity.h"

class GameObject;
class Component : public GameEntity
{
public:
	Component(GameObject* owner, INT32 order = 100);
	virtual ~Component();

	INT32 GetOrder() const;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	GameObject* GetOwner() { return _owner; }
protected:
	GameObject* _owner = nullptr;

private:
	INT32		_order = 100;
};

