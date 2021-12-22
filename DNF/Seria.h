#pragma once
#include "Character.h"
#include "Ibutton.h"

class ButtonComponent;
class AnimatorComponent;
class Seria : public Character, IButton
{
public:
	using Character::Character;
	virtual ~Seria() noexcept = default;

	virtual void Init() override;
private:
	virtual void OnIdle() override;
	virtual void OnHover() override;
	virtual void OnClick() override;
	virtual void OnExecute() override;

private:
	AnimatorComponent* mpAnimatorComp = nullptr;
};

