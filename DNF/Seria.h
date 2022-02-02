#pragma once
#include "GameObject.h"
#include "IButton.h"

class Seria : public GameObject, IButton
{
public:
	using GameObject::GameObject;
	virtual ~Seria()  = default;

	virtual void Init() override;
private:
	virtual void OnExecuteToIdle() override { }
	virtual void OnExecuteToClick() override;
};

