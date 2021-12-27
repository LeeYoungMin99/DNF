#pragma once
#include "Component.h"

class PlayerStatusComponent;
class PlayerTransformComponent;
class PlayerMovementComponent : public Component
{
public:
	using Component::Component;
	virtual ~PlayerMovementComponent()  = default;

	virtual void Init() override;
	virtual void Update() override;

	void						Move();
private:
	PlayerStatusComponent*		_statusComp = nullptr;
	PlayerTransformComponent*	_transformComp = nullptr;
	float						_moveSpeed = 0.0f;

	const float WALK_SPEED = 200.0f;
	const float RUN_SPEED = WALK_SPEED * 2.0f;
	const float Y_SPEED = WALK_SPEED;
};
