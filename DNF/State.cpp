#include "stdafx.h"
#include "State.h"

#include "StateMachineComponent.h"
#include "TransformComponent.h"
#include "PositionComponent.h"
#include "BodyCollisionComponent.h"
#include "RectColliderComponent.h"

#include "GameObject.h"

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

Damaged::Damaged(StateMachineComponent* stateMachine, GameObject* owner)
	:State(stateMachine, owner)
{
	_posComp = owner->GetComponent<PositionComponent>();
	_colliderComp = _owner->GetComponent<BodyCollisionComponent>()->GetCollider();
}

void Damaged::Init()
{
	_onGroundElapsedTime = 0;
	_changeStateTime = 0.5f;

	_acceleration = 0.0f;

	_bIsFloatOnce = false;
	_bOnGroundOnce = false;

	_bodyColliderSize = _colliderComp->GetRectSize();
}

void Damaged::Update()
{
	if (_onGroundElapsedTime >= _changeStateTime)
	{
		ChangeState(eState::Idle);
		return;
	}

	if (_posComp->GetZ() <= 0.0f)
	{
		_onGroundElapsedTime += Timer::GetDeltaTime();

		if (_bIsFloatOnce)
		{
			if (false == _bOnGroundOnce)
			{
				_bOnGroundOnce = true;

				_posComp->SetAcceleration(_acceleration);
				_posComp->SetResistance(_acceleration * 0.6f);
			}
		}
	}
	else
	{
		_onGroundElapsedTime = 0.0f;
		_bIsFloatOnce = true;
		_acceleration = _posComp->GetAccelerration();
	}

	if (_onGroundElapsedTime >= 0.6f)
	{
		_colliderComp->SetRectSize({ 0,0,0,0 });
	}

	if (_bIsFloatOnce)
	{
		_changeStateTime = 0.7f;
	}
}

void Damaged::Release()
{
	_colliderComp->SetRectSize(_bodyColliderSize);
}
