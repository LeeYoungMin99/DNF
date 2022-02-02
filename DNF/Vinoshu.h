#pragma once
#include "GameObject.h"

class Vinoshu : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~Vinoshu() = default;

	virtual void Init() override;
};

