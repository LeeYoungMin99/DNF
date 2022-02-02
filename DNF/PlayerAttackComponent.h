#pragma once
#include "Component.h"

class AnimatorComponent;
class StateMachineComponent;
class AttackCollisionComponent;
class PlayerAttackComponent : public Component
{
public:
	using Component::Component;
	virtual ~PlayerAttackComponent() = default;

	virtual void Init() override;
	virtual void Update() override;

	void SetAttack(const RECT& size, int top, int bottom, float floatingPower, float resistance = 0.0f);
private:
	StateMachineComponent*		_stateMachineComp = nullptr;
	AttackCollisionComponent*	_atkComp = nullptr;
	AnimatorComponent*			_animComp = nullptr;

	int _prevFrame = 0;
};

