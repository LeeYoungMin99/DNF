#include "stdafx.h"
#include "ButtonComponent.h"
#include "RectComponent.h"
#include "Button.h"

void ButtonComponent::Update()
{
	if (PtInRect(&(mpRectComponent->GetRect()), Input::GetMousePosition()))
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

void ButtonComponent::SetRectComponent(RectComponent* rectComponent) noexcept
{
	mpRectComponent = rectComponent;
}
