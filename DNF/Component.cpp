#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* owner, INT32 order) noexcept
	: mpOwner{ owner }, mOrder{ order }
{
	mpOwner->AddComponent(this);
}

Component::~Component() noexcept
{
	mpOwner->RemoveComponent(this);
	mpOwner = nullptr;
}

INT32 Component::GetOrder() const noexcept
{
	return mOrder;
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
