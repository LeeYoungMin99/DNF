#pragma once
#include "Component.h"

class PositionComponent;
class RectColliderComponent;
class GoblinStatusComponent;
class BodyCollisionComponent : public Component
{
public:
	BodyCollisionComponent(RectColliderComponent* rectColliderComp, int top, int bottom, GameObject* owner, INT32 order = 100);
	virtual ~BodyCollisionComponent() = default;

	RectColliderComponent*	GetCollider()		  { return _collider; }
	int						GetZTop() const;
	int						GetZBottom() const;

	void					OnCollided(const RECT& collisionRect);
	void					OnCollided(float floatingPower);
private:
	int						_zTop = 0;
	int						_zBottom = 0;

	PositionComponent*		_posComp = nullptr;
	RectColliderComponent*	_collider = nullptr;

	// 일단 고블린만 피격될 수 있게 만들었음
	GoblinStatusComponent*	_goblinStatusComp = nullptr;
};

