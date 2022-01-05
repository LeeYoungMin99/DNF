#include "stdafx.h"
#include "MonsterState.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "StateMachineComponent.h"
#include "AttackCollisionComponent.h"
#include "AnimatorComponent.h"
#include "Animation.h"

#include "Scene.h"

Meet::Meet(StateMachineComponent* stateMachine, GameObject* owner)
	:State(stateMachine, owner)
{
	_animComp = owner->GetComponent<AnimatorComponent>();
}

void Meet::Update()
{
	if (_animComp->GetCurAnim()->IsEnd())
	{
		ChangeState(eState::Idle);
	}
}

Idle::Idle(StateMachineComponent* stateMachine, GameObject* owner)
	:State(stateMachine, owner)
{
	_transformComp = owner->GetComponent<TransformComponent>();

	for (auto& obj : owner->GetScene()->GetObjects())
	{
		if (obj->GetTag() == L"Player")
		{
			_target = obj;
		}
	}
}

void Idle::Init()
{
	_elapsedTime = 0.0f;

	if (_target->GetX() > _owner->GetX())
	{
		_transformComp->SetDirX(TransformComponent::eDirX::Right);
	}
	else
	{
		_transformComp->SetDirX(TransformComponent::eDirX::Left);
	}
}

void Idle::Update()
{
	_elapsedTime += Timer::GetDeltaTime();

	if (_target->GetX() > _owner->GetX())
	{
		_transformComp->SetDirX(TransformComponent::eDirX::Right);
	}
	else
	{
		_transformComp->SetDirX(TransformComponent::eDirX::Left);
	}

	if (_elapsedTime >= CHANGE_STATE_TIME)
	{
		ChangeState(eState::Walk);
	}
}

Walk::Walk(StateMachineComponent* stateMachine, GameObject* owner)
	:State(stateMachine, owner)
{
	_transformComp = owner->GetComponent<TransformComponent>();

	for (auto& obj : owner->GetScene()->GetObjects())
	{
		if (obj->GetTag() == L"Player")
		{
			_target = obj;
		}
	}
}

void Walk::Init()
{
	_elapsedTime = 0.0f;

	if (_target->GetX() > _owner->GetX())
	{
		_transformComp->SetDirX(TransformComponent::eDirX::Right);
	}
	else
	{
		_transformComp->SetDirX(TransformComponent::eDirX::Left);
	}
}

void Walk::Update()
{
	_elapsedTime += Timer::GetDeltaTime();

	ChangeDir();

	//Move();

	if (_elapsedTime >= CHANGE_STATE_TIME)
	{
		if (_changeCount >= CAN_CHANGE_SPECIAL_PATTERN)
		{
			ChangeState(eState::Skill1);
			_changeCount = 0;
		}
		else
		{
			ChangeState(eState::AttackReady);
		}
	}
}

void Walk::Move()
{
	int distanceX = abs(_target->GetX() - _owner->GetX());
	int distanceY = abs(_target->GetY() - _owner->GetY());

	if (distanceX >= NOT_MOVE_X_DISTANCE)
	{
		_owner->AddX((MOVE_SPEED_X * Timer::GetDeltaTime()) * (int)_transformComp->GetDirX());
	}

	if (distanceY >= NOT_MOVE_Y_DISTANCE)
	{
		_owner->AddY((MOVE_SPEED_Y * Timer::GetDeltaTime()) * (int)_transformComp->GetDirY());
	}
}

void Walk::ChangeDir()
{
	if (_target->GetX() > _owner->GetX())
	{
		_transformComp->SetDirX(TransformComponent::eDirX::Right);
	}
	else
	{
		_transformComp->SetDirX(TransformComponent::eDirX::Left);
	}

	if (_target->GetY() > _owner->GetY())
	{
		_transformComp->SetDirY(TransformComponent::eDirY::Down);
	}
	else
	{
		_transformComp->SetDirY(TransformComponent::eDirY::Up);
	}
}

AttackReady::AttackReady(StateMachineComponent* stateMachine, GameObject* owner)
	:State(stateMachine, owner)
{
	_transformComp = _owner->GetComponent<TransformComponent>();

	for (auto& obj : owner->GetScene()->GetObjects())
	{
		if (obj->GetTag() == L"Player")
		{
			_target = obj;
		}
	}
}

void AttackReady::Init()
{
	if (_transformComp->GetDirX() == TransformComponent::eDirX::Right)
	{
		_trackPos = { _target->GetX() - 100, _target->GetY() };
	}
	else
	{
		_trackPos = { _target->GetX() + 100, _target->GetY() };
	}

	_elapsedTime = 0.0f;
}

void AttackReady::Update()
{
	_elapsedTime += Timer::GetDeltaTime();

	if (_elapsedTime > TARGET_TIME) { _elapsedTime = TARGET_TIME; }

	POINT targetPos = { (_trackPos.x - _owner->GetX()) * (_elapsedTime / TARGET_TIME) ,(_trackPos.y - _owner->GetY()) * (_elapsedTime / TARGET_TIME) };

	_owner->AddX(targetPos.x);
	_owner->AddY(targetPos.y);

	if (_elapsedTime >= TARGET_TIME)
	{
		ChangeState(eState::NormalAttack1);
	}
}

NormalAttack::NormalAttack(StateMachineComponent* stateMachine, GameObject* owner)
	:State(stateMachine,owner)
{
	_attackCollider = owner->GetComponent<AttackCollisionComponent>();
}

void NormalAttack::Init()
{
	_attackCollider->Init();
}

void NormalAttack::Update()
{
	if (_owner->GetComponent<AnimatorComponent>()->GetCurAnim()->IsEnd())
	{
		ChangeState(eState::Idle);
	}
}
