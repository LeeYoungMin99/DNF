#pragma once
#include "Component.h"

class GameObject;
class newAnimatorComponent;
class newSpriteComponent : public Component
{
public:
	newSpriteComponent(newAnimatorComponent* animatorComp, GameObject* owner, INT32 order = 100) noexcept;
	virtual ~newSpriteComponent() noexcept = default;

	virtual void Render() override;
private:
	newAnimatorComponent* mpAnimatorComp = nullptr;
};

