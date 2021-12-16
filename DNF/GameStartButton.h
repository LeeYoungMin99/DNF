#pragma once
#include "GameObject.h"

template <typename T>
class ButtonComponent;

class AnimatorComponent;
class GameStartButton : public GameObject
{
private:
	using ButtonComponent = ButtonComponent<GameStartButton>;

public:
	using GameObject::GameObject;
	virtual ~GameStartButton() noexcept = default;

	virtual void Init() override;

private:
	void SetIdle();
	void SetHover();
	void SetClick();
	void SetExecute();

private:
	AnimatorComponent* mpAnimatorComp = nullptr;
};
