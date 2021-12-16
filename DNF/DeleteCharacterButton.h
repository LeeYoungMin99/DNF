#pragma once
#include "GameObject.h"

template <typename T>
class ButtonComponent;

class AnimatorComponent;
class DeleteCharacterButton : public GameObject
{
private:
	using ButtonComponent = ButtonComponent<DeleteCharacterButton>;

public:
	using GameObject::GameObject;
	virtual ~DeleteCharacterButton() noexcept = default;

	virtual void Init() override;

private:
	void SetIdle();
	void SetHover();
	void SetClick();
	void SetExecute();

private:
	AnimatorComponent* mpAnimatorComp = nullptr;
};
