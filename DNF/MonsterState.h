#pragma once
#include "State.h"

class AnimatorComponent;
class Meet : public State
{
public:
	Meet(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~Meet() = default;

	virtual void Update();
private:
	AnimatorComponent* _animComp = nullptr;
};

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

	virtual void Init();
	virtual void Update();

	void Move();
	void ChangeDir();
private:
	GameObject* _target = nullptr;
	TransformComponent* _transformComp = nullptr;

	const float MOVE_SPEED_X = 200.0f;
	const float MOVE_SPEED_Y = 150.0f;
	
	const int NOT_MOVE_X_DISTANCE = 5;
	const int NOT_MOVE_Y_DISTANCE = 5;

	float _elapsedTime = 0.0f;

	int _changeCount = 0;

	const int CAN_CHANGE_SPECIAL_PATTERN = 4;
	const float CHANGE_STATE_TIME = 2.0f;
};

class GameObject;
class TransformComponent;
class AttackReady : public State
{
public:
	AttackReady(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~AttackReady() = default;

	virtual void Init() override;
	virtual void Update() override;
private:
	GameObject* _target = nullptr;
	TransformComponent* _transformComp = nullptr;

	POINT _trackPos = {};

	float _elapsedTime = 0.0f;
	const float TARGET_TIME = 0.32;
};