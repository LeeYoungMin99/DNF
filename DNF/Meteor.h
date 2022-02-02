#pragma once
#include "GameObject.h"

class Meteor : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~Meteor() = default;

	virtual void Init() override;
};

