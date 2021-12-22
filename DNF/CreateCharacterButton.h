#pragma once
#include "GameObject.h"
#include "Ibutton.h"

class ButtonComponent;
class AnimatorComponent;
class CreateCharacterButton : public GameObject, IButton
{
public:
	using GameObject::GameObject;
	virtual ~CreateCharacterButton() noexcept = default;

	virtual void Init() override;

private:
	virtual void OnIdle() override;
	virtual void OnHover() override;
	virtual void OnClick() override;
	virtual void OnExecute() override;

private:
	AnimatorComponent* mpAnimatorComp = nullptr;
};
