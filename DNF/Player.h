#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~Player()  = default;

	virtual void Init() override;
};

