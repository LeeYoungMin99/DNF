#pragma once
#include "Component.h"

class RectComponent;

template <typename Type>
class ButtonComponent : public Component
{
private:
	using t = Type;
	using callback_t = void(Type::*)();

	enum class eButtonState { Idle, Hover, Click, };
public:
	struct ButtonFunction
	{
		ButtonFunction(
			callback_t setIdle,
			callback_t setHover,
			callback_t setClick,
			callback_t setExecute)
		{
			callbackSetIdle = setIdle;
			callbackSetHover = setHover;
			callbackSetClick = setClick;
			callbackExecute = setExecute;
		}
		~ButtonFunction() noexcept = default;

		callback_t callbackSetIdle = nullptr;
		callback_t callbackSetHover = nullptr;
		callback_t callbackSetClick = nullptr;
		callback_t callbackExecute = nullptr;
	};
public:
	ButtonComponent(RectComponent* rectComponent,
		t* type,
		ButtonFunction btnFucn,
		GameObject* owner, INT32 order = 100)
		:Component(owner, order)
	{
		mpType = type;
		mpCallbackSetIdle = btnFucn.callbackSetIdle;
		mpCallbackSetHover = btnFucn.callbackSetHover;
		mpCallbackSetClick = btnFucn.callbackSetClick;
		mpCallbackExecute = btnFucn.callbackExecute;
		mpRectComponent = rectComponent;
	}
	virtual ~ButtonComponent() noexcept = default;

	virtual void Update() override
	{
		const RECT* mCollisionRect = mpRectComponent->GetRectAddress();

		switch (mState)
		{
		case eButtonState::Idle:
			if (PtInRect(mCollisionRect, Input::GetMousePosition()))
			{
				(mpType->*mpCallbackSetHover)();
				mState = eButtonState::Hover;
			}
			break;
		case eButtonState::Hover:
			if (false == PtInRect(mCollisionRect, Input::GetMousePosition()))
			{
				(mpType->*mpCallbackSetIdle)();
				mState = eButtonState::Idle;
			}
			else if (Input::GetButton(VK_LBUTTON))
			{
				(mpType->*mpCallbackSetClick)();
				mState = eButtonState::Click;
			}
			break;
		case eButtonState::Click:
			if (false == PtInRect(mCollisionRect, Input::GetMousePosition()))
			{
				(mpType->*mpCallbackSetIdle)();
				mState = eButtonState::Idle;
			}
			else if (Input::GetButtonUp(VK_LBUTTON))
			{
				(mpType->*mpCallbackExecute)();
			}
			break;
		}
	}

private:
	t* mpType = nullptr;
	callback_t mpCallbackSetIdle = nullptr;
	callback_t mpCallbackSetHover = nullptr;
	callback_t mpCallbackSetClick = nullptr;
	callback_t mpCallbackExecute = nullptr;

	RectComponent* mpRectComponent = nullptr;
	eButtonState mState = eButtonState::Idle;
};
