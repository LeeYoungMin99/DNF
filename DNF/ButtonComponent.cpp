#include "stdafx.h"
#include "ButtonComponent.h"
#include "RectComponent.h"
#include "Button.h"

ButtonComponent::ButtonComponent(RectComponent* rectComponent, GameObject* owner, INT32 order)
	:Component(owner, order)
{
	mpRectComponent = rectComponent;
}

void ButtonComponent::Update()
{
	if (PtInRect(mpRectComponent->GetRectAddress(), Input::GetMousePosition()))
	{
		((Button*)mpOwner)->SetState(Button::eButtonState::Hover);

		if (Input::GetButton(VK_LBUTTON))
		{
			((Button*)mpOwner)->SetState(Button::eButtonState::Click);
		}
	}
	else
	{
		((Button*)mpOwner)->SetState(Button::eButtonState::Idle);
	}
}
