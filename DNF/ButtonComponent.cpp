#include "stdafx.h"
#include "ButtonComponent.h"

#include "RectColliderComponent.h"
#include "Ibutton.h"
#include "GameObject.h"

ButtonComponent::ButtonComponent(RectColliderComponent* rectComponent, IButton* obj, GameObject* owner, INT32 order)
	:Component(owner, order)
{
	_object = obj;
	_rectComp = rectComponent;
}

void ButtonComponent::Update()
{
	const RECT mCollisionRect = _rectComp->GetRect();

	switch (_state)
	{
	case eButtonState::Idle:
		if (PtInRect(&mCollisionRect, Input::GetMousePosition()))			{ _state = eButtonState::Hover; }
		break;
	case eButtonState::Hover:
		if (false == PtInRect(&mCollisionRect, Input::GetMousePosition()))	{ _state = eButtonState::Idle; }
		else if (Input::GetButton(VK_LBUTTON))								{ _state = eButtonState::Click; }
		break;
	case eButtonState::Click:
		if (false == PtInRect(&mCollisionRect, Input::GetMousePosition()))	{ _state = eButtonState::Idle; }
		else if (Input::GetButtonUp(VK_LBUTTON))							{ _object->OnExecute();	}
		break;
	}
}