#include "stdafx.h"
#include "ButtonComponent.h"

#include "RectComponent.h"
#include "Ibutton.h"

ButtonComponent::ButtonComponent(RectComponent* rectComponent, IButton* obj, GameObject* owner, INT32 order)
	:Component(owner, order)
{
	mpObj = obj;
	mpRectComponent = rectComponent;
}

void ButtonComponent::Update()
{
	const RECT* mCollisionRect = mpRectComponent->GetRectAddress();

	switch (mState)
	{
	case eButtonState::Idle:
		if (PtInRect(mCollisionRect, Input::GetMousePosition()))
		{
			mpObj->OnHover();
			mState = eButtonState::Hover;
		}
		break;
	case eButtonState::Hover:
		if (false == PtInRect(mCollisionRect, Input::GetMousePosition()))
		{
			mpObj->OnIdle();
			mState = eButtonState::Idle;
		}
		else if (Input::GetButton(VK_LBUTTON))
		{
			mpObj->OnClick();
			mState = eButtonState::Click;
		}
		break;
	case eButtonState::Click:
		if (false == PtInRect(mCollisionRect, Input::GetMousePosition()))
		{
			mpObj->OnIdle();
			mState = eButtonState::Idle;
		}
		else if (Input::GetButtonUp(VK_LBUTTON))
		{
			mpObj->OnExecute();
		}
		break;
	}
}
