#pragma once
#include "GameEntity.h"

enum class eState;
class GameObject;
class StateMachineComponent;
class State : public IBehaviour
{
public:
	State(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~State() = default;

	virtual void Init() override {}
	virtual void Update() override {}
	virtual void Render() override {}
	virtual void Release() override {}

	void ChangeState(eState state);
	void ChangeState(int stateTag);
protected:
	StateMachineComponent*	_stateMachineComp = nullptr;
	GameObject*				_owner = nullptr;
};

class PositionComponent;
class RectColliderComponent;
class Damaged : public State 
{
public:
	Damaged(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~Damaged() = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;

	bool					GetOnGroundOnce()			{ return _bOnGroundOnce; }
	bool					GetIsFloatOnce()			{ return _bIsFloatOnce; }
	float					GetGroundElapsedTime()		{ return _onGroundElapsedTime; }
private:
	PositionComponent*		_posComp = nullptr;
	RectColliderComponent*	_colliderComp = nullptr;

	float					_onGroundElapsedTime = 0.0f;

	bool					_bOnGroundOnce = false;
	bool					_bIsFloatOnce = false;

	float					_changeStateTime = 0.4f;

	float					_acceleration = 0.0f;

	RECT					_bodyColliderSize = {};
};
