#pragma once
#include "GameObject.h"

template <typename T>
class ButtonComponent;

class AnimatorComponent;
class GameShutDownButton : public GameObject
{
private:
	using ButtonComponent = ButtonComponent<GameShutDownButton>;

public:
	using GameObject::GameObject;
	virtual ~GameShutDownButton() noexcept = default;

	virtual void Init() override;

private:
	void SetIdle();
	void SetHover();
	void SetClick();
	void SetExecute();

private:
	AnimatorComponent* mpAnimatorComp = nullptr;
};
