#pragma once
#include "Component.h"

class RectComponent;
class ButtonComponent : public Component
{
public:
	ButtonComponent(RectComponent* rectComponent, GameObject* owner, INT32 order = 100);
	virtual ~ButtonComponent() noexcept = default;

	virtual void Update() override;
private:
	RectComponent* mpRectComponent = nullptr;
};
