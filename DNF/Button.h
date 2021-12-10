#pragma once
#include "GameObject.h"

class Button : public GameObject
{
public:
	enum class eButtonState { Idle, Hover, Click };
	using GameObject::GameObject;

	virtual void Init() override;

	void SetState(eButtonState state);
	eButtonState GetState()
private:
	eButtonState mState = eButtonState::Idle;
};
