#include "stdafx.h"
#include "Button.h"

#include "RectComponent.h"
#include "ButtonComponent.h"

void Button::Init()
{
	RectComponent* bodyCollisionRect = new RectComponent(this);
	ButtonComponent* button = new ButtonComponent(bodyCollisionRect,this);
}

void Button::SetState(eButtonState state)
{
	mState = state;
}
