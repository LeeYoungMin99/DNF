#pragma once
#include "GameEntity.h"

class GameObject;
class StateMachineComponent;
class State : public GameEntity
{
public:
	State(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~State() = default;

	virtual void Init() override {}
	virtual void Update() override {}
	virtual void Render() override {}
	virtual void Release() override {}
protected:
	StateMachineComponent*	_stateMachineComp = nullptr;
	GameObject*				_owner = nullptr;
};