#pragma once
#include "Component.h"

class AnimatorComponent;
class PlayerStatusComponent;
class AttackCollisionComponent;
class PlayerAttackComponent : public Component
{
public:
	using Component::Component;
	virtual ~PlayerAttackComponent() = default;

	virtual void Init() override;
	virtual void Update() override;

	void SetAttack(const RECT& size,int top,int bottom,float floatingPower);
private:
	PlayerStatusComponent*		_statusComp = nullptr;
	AttackCollisionComponent*	_atkComp = nullptr;
	AnimatorComponent*			_animComp = nullptr;
};

