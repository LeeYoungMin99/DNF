#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* owner, INT32 order) noexcept
	: mOwner{ owner }, mOrder{ order }
{
	mOwner->AddComponent(this);
}

Component::~Component() noexcept
{
	mOwner->RemoveComponent(this);
	mOwner = nullptr;
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

void Component::Render(HDC hdc)
{
}

void Component::Release()
{
}
