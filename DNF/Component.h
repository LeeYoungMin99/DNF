#pragma once

#include "GameEntity.h"

class GameObject;
class Component : public IBehaviour
{
public:
	Component(GameObject* owner, INT32 order = 100);
	virtual ~Component();

	virtual void Init() override { }
	virtual void Update() override { }
	virtual void Render() override { }
	virtual void Release() override { }

	INT32			GetOrder() const { return _order; }
	GameObject*		GetOwner()		 { return _owner; }
private:
	GameObject*		_owner = nullptr;
	INT32			_order = 100;
};

