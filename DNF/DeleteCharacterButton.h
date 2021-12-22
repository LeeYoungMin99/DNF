#pragma once
#include "GameObject.h"
#include "Ibutton.h"

class ButtonComponent;
class AnimatorComponent;
class DeleteCharacterButton : public GameObject, IButton
{
public:
	using GameObject::GameObject;
	virtual ~DeleteCharacterButton() noexcept = default;

	virtual void Init() override;

private:
	virtual void OnIdle() override;
	virtual void OnHover() override;
	virtual void OnClick() override;
	virtual void OnExecute() override;

private:
	AnimatorComponent* mpAnimatorComp = nullptr;
};
