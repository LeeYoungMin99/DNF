#pragma once
#include "GameObject.h"

class Button : public GameObject
{
public:
	enum class eButtonState { Idle, Hover, Click };
public:
	using GameObject::GameObject;

	virtual void Init() override;

	void SetState(eButtonState state);
protected:
	eButtonState mState = eButtonState::Idle;
};
