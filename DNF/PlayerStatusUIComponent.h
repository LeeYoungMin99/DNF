#pragma once
#include "Component.h"

class Image;
class PlayerHealthBar;
class PlayerStatusUIComponent : public Component
{
public:
	using Component::Component;
	virtual ~PlayerStatusUIComponent() noexcept = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
private:
	Image* mpPlayerStatusUI = nullptr;
	PlayerHealthBar* mpHPBar = nullptr;
	PlayerHealthBar* mpMPBar = nullptr;
};

