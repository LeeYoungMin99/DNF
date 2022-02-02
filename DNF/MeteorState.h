#pragma once
#include "State.h"

class AnimatorComponent;
class MeteorIdle : public State
{
public:
	MeteorIdle(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~MeteorIdle() = default;

	virtual void Update() override;
private:
	AnimatorComponent* _animComp = nullptr;

};

class PositionComponent;
class AttackCollisionComponent;
class MeteorAttack : public State
{
public:
	MeteorAttack(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~MeteorAttack() = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;

	void SetPos(const int& curX, const float& curZ);
private:
	PositionComponent* _posComp = nullptr;
	AttackCollisionComponent* _atkComp = nullptr;

	float _startPointX = {};
	float _startPointZ = {};
	float _targetPointX = {};
	float _targetPointZ = {};

	float _elapsedTime = 0.0f;
	const float TARGET_TIME = 1.0f;

	const float DISTANCE = 500.0f;
};

class AnimatorComponent;
class AttackCollisionComponent;
class MeteorSkill : public State
{
public:
	MeteorSkill(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~MeteorSkill() = default;

	virtual void Update() override;
private:
	AnimatorComponent* _animComp = nullptr;
	AttackCollisionComponent* _atkComp = nullptr;

};