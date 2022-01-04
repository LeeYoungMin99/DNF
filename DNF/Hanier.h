#pragma once
#include "GameObject.h"

class Hanier : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~Hanier() = default;

	virtual void Init();
};

