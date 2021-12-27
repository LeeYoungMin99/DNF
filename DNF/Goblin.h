#pragma once
#include "GameObject.h"

class Goblin : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~Goblin() = default;

	virtual void Init() override;
};

