#pragma once
#include "Character.h"

template <typename T>
class ButtonComponent;

class AnimatorComponent;
class Seria : public Character
{
private:
	using ButtonComponent = ButtonComponent<Seria>;

public:
	using Character::Character;
	virtual ~Seria() noexcept = default;

	virtual void Init() override;

private:
	void SetIdle();
	void SetHover();
	void SetClick();
	void SetExecute();

private:
	AnimatorComponent* mpAnimatorComp = nullptr;
};

