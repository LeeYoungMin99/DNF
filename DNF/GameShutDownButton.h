#pragma once
#include "GameObject.h"
#include "IButton.h"

class ButtonComponent;
class AnimatorComponent;
class GameShutDownButton : public GameObject, IButton
{
public:
	using GameObject::GameObject;
	virtual ~GameShutDownButton() noexcept = default;

	virtual void Init() override;

private:
	virtual void OnIdle() override;
	virtual void OnHover() override;
	virtual void OnClick() override;
	virtual void OnExecute() override;

private:
	AnimatorComponent* mpAnimatorComp = nullptr;
};
