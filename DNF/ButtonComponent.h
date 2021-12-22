#pragma once
#include "Component.h"

struct IButton;
class RectComponent;
class ButtonComponent : public Component
{
private:
	enum class eButtonState { Idle, Hover, Click, };
public:
	ButtonComponent(RectComponent* rectComponent, IButton* obj, GameObject* owner, INT32 order = 100);
	virtual ~ButtonComponent() noexcept = default;

	virtual void Update() override;

private:
	IButton* mpObj = nullptr;

	RectComponent* mpRectComponent = nullptr;
	eButtonState mState = eButtonState::Idle;
};