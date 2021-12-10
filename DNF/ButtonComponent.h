#pragma once
#include "Component.h"

class RectComponent;
class ButtonComponent : public Component
{
public:
	using Component::Component;
	virtual ~ButtonComponent() noexcept = default;

	virtual void Update() override;

	void SetRectComponent(RectComponent* rectComponent) noexcept;
private:
	RectComponent* mpRectComponent = nullptr;
};
