#pragma once
#include "Component.h"

class AnimatorComponent;
class RendererComponent : public Component
{
public:
	RendererComponent(AnimatorComponent* animatorComp, GameObject* owner, INT32 order = 100) noexcept;
	virtual ~RendererComponent() noexcept = default;

	virtual void Render() override;
private:
	AnimatorComponent* mpAnimatorComp = nullptr;
};

