#include "stdafx.h"
#include "Button.h"

#include "RectComponent.h"
#include "ButtonComponent.h"

void Button::Init()
{
	ButtonComponent* button = new ButtonComponent(new RectComponent(this), this);
	GameObject::Init();
}

void Button::SetState(eButtonState state) noexcept
{
	mState = state;
}
