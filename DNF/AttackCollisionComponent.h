#pragma once
#include "Component.h"

class PositionComponent;
class RectColliderComponent;
class AttackCollisionComponent : public Component
{
public:
	AttackCollisionComponent(RectColliderComponent* rectColliderComp, GameObject* owner, INT32 order = 100);
	virtual ~AttackCollisionComponent() = default;

	virtual void Init() override;

	RectColliderComponent*	GetCollider()				{ return _collider; }
	float					GetFloatingPower()	const	{ return _floatingPower; }
	float					GetStrikingPower()	const	{ return _strikingPower; }
	float					GetResistance()		const	{ return _resistance; }
	vector<GameObject*>		GetHitObjs()		const	{ return _hitObjs; }
	float					GetZTop()			const;
	float					GetZBottom()		const;

	void					SetAttack(const RECT& size, int top, int bottom, float floatingPower,float resistance = 0.0f);

	void					AddHitObj(GameObject* hitChar) { _hitObjs.push_back(hitChar); }
	
	void					ClearHitObjs() { _hitObjs.clear(); }
private:
	RectColliderComponent*	_collider = nullptr;
	PositionComponent*		_posComp = nullptr;

	int						_zTop = 0;
	int						_zBottom = 0;
	float					_strikingPower = 0.0f;
	float					_floatingPower = 0.0f;
	float					_resistance = 0.0f;
	vector<GameObject*>		_hitObjs = {};
};

