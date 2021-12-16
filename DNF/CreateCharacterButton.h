#pragma once
#include "GameObject.h"

template <typename T>
class ButtonComponent;

class AnimatorComponent;
class CreateCharacterButton : public GameObject
{
private:	
	using ButtonComponent = ButtonComponent<CreateCharacterButton>;

public:
	using GameObject::GameObject;
	virtual ~CreateCharacterButton() noexcept = default;

	virtual void Init() override;

private:
	void SetIdle();
	void SetHover();
	void SetClick();
	void SetExecute();

private:
	AnimatorComponent* mpAnimatorComp = nullptr;
};
