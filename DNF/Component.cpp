#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* owner, INT32 order) 
	: _owner{ owner }, _order{ order }
{
	_owner->AddComponent(this);
}

Component::~Component() 
{
	_owner->RemoveComponent(this);
	_owner = nullptr;
}
