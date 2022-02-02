#pragma once
#include "Component.h"

class PositionComponent;
class RectColliderComponent;
class StateMachineComponent;
class BodyCollisionComponent : public Component
{
public:
	BodyCollisionComponent(RectColliderComponent* rectColliderComp, float top, float bottom, GameObject* owner, INT32 order = 100);
	virtual ~BodyCollisionComponent() = default;

	RectColliderComponent*	GetCollider()		  { return _collider; }
	float					GetZTop() const;
	float					GetZBottom() const;

	void					OnCollided(const RECT& collisionRect);
	void					OnCollided(float damage, float floatingPower,float resistance = 0.0f);
private:
	float					_zTop = 0;
	float					_zBottom = 0;

	PositionComponent*		_posComp = nullptr;
	RectColliderComponent*	_collider = nullptr;

	bool					_bIsSuperArmor = false;
	StateMachineComponent*	_stateMachineComp = nullptr;
};

