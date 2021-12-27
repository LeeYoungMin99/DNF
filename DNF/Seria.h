#pragma once
#include "Ibutton.h"
#include "GameObject.h"

class Seria : public GameObject, IButton
{
public:
	using GameObject::GameObject;
	virtual ~Seria()  = default;

	virtual void Init() override;
private:
	virtual void OnExecute() override;
};

