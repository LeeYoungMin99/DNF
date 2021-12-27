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

INT32 Component::GetOrder() const 
{
	return _order;
}

void Component::Init()
{
}

void Component::Update()
{
}

void Component::Render()
{
}

void Component::Release()
{
}
