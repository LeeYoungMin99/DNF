#pragma once
#include "Component.h"

struct IButton;
class RectColliderComponent;
class ButtonComponent : public Component
{
public:
	enum class eButtonState 
	{ 
		None,
		Idle, 
		Hover, 
		Click
	};
public:
	ButtonComponent(RectColliderComponent* rectComponent, IButton* obj, GameObject* owner, INT32 order = 100);
	virtual ~ButtonComponent() = default;

	virtual void Update() override;

	eButtonState			GetState() const { return _state; }
private:
	IButton*				_object = nullptr;
	eButtonState			_state = eButtonState::Idle;
	RectColliderComponent*	_rectComp = nullptr;
};

