#pragma once
#include "GameObject.h"

class Button : public GameObject
{
public:
	enum class eButtonState { Idle, Hover, Click };
public:
	using GameObject::GameObject;
	virtual ~Button() noexcept = default;

	virtual void Init() override;

	void SetState(eButtonState state) noexcept;
protected:
	eButtonState mState = eButtonState::Idle;
};
