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

void StateMachineComponent::ChangeState(eState state)
{
	if (nullptr != _curState)
	{
		_curState->Release();
	}

	_curState = _states[state];
	_curStateTag = state;
	_curState->Init();
}

void StateMachineComponent::ChangeState(int stateTag)
{
	ChangeState((eState)stateTag);
}
