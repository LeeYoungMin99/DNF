#pragma once
#include "State.h"

class GameObject;
class TransformComponent;
class Idle : public State
{
public:
	Idle(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~Idle() = default;

	virtual void Init();
	virtual void Update();
private:
	GameObject* _target = nullptr;
	TransformComponent* _transformComp = nullptr;
	float _elapsedTime = 0.0f;

	const float CHANGE_STATE_TIME = 0.5f;
};

class GameObject;
class TransformComponent;
class Walk : public State
{
public:
	Walk(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~Walk() = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;

	void					Move();
	void					ChangeDir();

	GameObject*				GetTarget() { return _target; }
private:
	GameObject*				_target = nullptr;
	TransformComponent*		_transformComp = nullptr;

	bool					_bCanChangeDirX = false;
	bool					_bCanChangeDirY = false;

	float					_elapsedTime = 0.0f;
	float					_changeTimeDirX = 0.0f;
	float					_changeTimeDirY = 0.0f;

	const float MOVE_SPEED_X = 200.0f;
	const float MOVE_SPEED_Y = 150.0f;

	const int CAN_CHANGE_X_DISTANCE = 3;
	const int CAN_CHANGE_Y_DISTANCE = 3;

	const float CHANGE_STATE_TIME = 4.0f;
	const float CHANGE_DIR_TIME = 0.8f;
};

class GameObject;
class AnimatorComponent;
class AttackReady : public State
{
public:
	AttackReady(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~AttackReady() = default;

	virtual void Update() override;
private:
	GameObject*			_target = nullptr;
	GameObject*			_meteor = nullptr;
	
	AnimatorComponent*	_animComp = nullptr;

	float				_elapsedTime = 0.0f;
};

class AttackCollisionComponent;
class AnimatorComponent;
class NormalAttack : public State
{
public:
	NormalAttack(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~NormalAttack() = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;
private:
	AttackCollisionComponent*	_attackCollider = nullptr;
	AnimatorComponent*			_animComp = nullptr;
};