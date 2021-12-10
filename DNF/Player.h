#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~Player() noexcept = default;
	
	virtual void Init() override;
	virtual void Update() override;
};

