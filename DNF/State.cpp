#include "stdafx.h"
#include "State.h"

#include "StateMachineComponent.h"

State::State(StateMachineComponent* stateMachine, GameObject* owner)
	:_stateMachineComp{ stateMachine }, _owner{ owner } { }