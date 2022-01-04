#include "stdafx.h"
#include "State.h"

#include "StateMachineComponent.h"
#include "TransformComponent.h"

State::State(StateMachineComponent* stateMachine, GameObject* owner)
	:_stateMachineComp{ stateMachine }, _owner{ owner } { }

void State::ChangeState(eState state)
{
	_stateMachineComp->ChangeState((int)state);
}

void State::ChangeState(int stateTag)
{
	_stateMachineComp->ChangeState(stateTag);
}