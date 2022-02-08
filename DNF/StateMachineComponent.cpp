#include "stdafx.h"
#include "StateMachineComponent.h"

#include "State.h"

StateMachineComponent::~StateMachineComponent()
{
	for (auto& state : _states)
	{
		SAFE_RELEASE(state.second);
	}

	_states.clear();
}

void StateMachineComponent::Update()
{
	_curState->Update();
}

void StateMachineComponent::ChangeState(int stateTag)
{
	if (_curState != nullptr)
	{
		_curState->Release();
	}
	_curState = _states[stateTag];
	_curStateTag = stateTag;
	_curState->Init();
}

void StateMachineComponent::ChangeState(eState state)
{
	ChangeState((int)state);
}