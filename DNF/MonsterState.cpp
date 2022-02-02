#include "stdafx.h"
#include "MonsterState.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "StateMachineComponent.h"
#include "AttackCollisionComponent.h"
#include "AnimatorComponent.h"
#include "Animation.h"

#include "Scene.h"

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
		_transformComp->SetDirX(eDirX::Right);
	}
	else
	{
		_transformComp->SetDirX(eDirX::Left);
	}
}

void Idle::Update()
{
	_elapsedTime += Timer::GetDeltaTime();

	if (_target->GetX() > _owner->GetX())
	{
		_transformComp->SetDirX(eDirX::Right);
	}
	else
	{
		_transformComp->SetDirX(eDirX::Left);
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
	_changeTimeDirX = 0.0f;
	_changeTimeDirY = 0.0f;

	if (_target->GetX() > _owner->GetX())
	{
		_transformComp->SetDirX(eDirX::Right);
	}
	else
	{
		_transformComp->SetDirX(eDirX::Left);
	}
}

void Walk::Update()
{
	float deltaTime = Timer::GetDeltaTime();

	_elapsedTime += deltaTime;

	if (true == _bCanChangeDirX)
	{
		_changeTimeDirX += deltaTime;
	}

	if (true == _bCanChangeDirY)
	{
		_changeTimeDirY += deltaTime;
	}

	ChangeDir();

	Move();

	if (_elapsedTime >= CHANGE_STATE_TIME)
	{
		if (abs(_target->GetX() - _owner->GetX()) <= 150 && abs(_target->GetY() - _owner->GetY()) <= 25)
		{
			ChangeState(eState::NormalAttack1);
		}
		else
		{
			ChangeState(eState::AttackReady);
		}
	}
}

void Walk::Release()
{
	if (_target->GetX() > _owner->GetX())
	{
		_transformComp->SetDirX(eDirX::Right);
	}
	else
	{
		_transformComp->SetDirX(eDirX::Left);
	}
}

void Walk::Move()
{
	_owner->AddX((LONG)((MOVE_SPEED_X * Timer::GetDeltaTime()) * (int)_transformComp->GetDirX()));
	_owner->AddY((LONG)((MOVE_SPEED_Y * Timer::GetDeltaTime()) * (int)_transformComp->GetDirY()));
}

void Walk::ChangeDir()
{
	int distanceX = _target->GetX() - _owner->GetX();
	int distanceY = _target->GetY() - _owner->GetY();
	eDirX dirX = _transformComp->GetDirX();

	if (abs(distanceX) <= CAN_CHANGE_X_DISTANCE || (distanceX >= 300 && dirX == eDirX::Left) || (distanceX <= -300 && dirX == eDirX::Right))
	{
		_bCanChangeDirX = true;
	}

	if (abs(distanceY) <= CAN_CHANGE_Y_DISTANCE)
	{
		_bCanChangeDirY = true;
	}

	if (_changeTimeDirX >= CHANGE_DIR_TIME)
	{
		_transformComp->ChangeDirX();
		_changeTimeDirX = 0.0f;
		_bCanChangeDirX = false;
	}

	if (_changeTimeDirY >= CHANGE_DIR_TIME)
	{
		_transformComp->ChangeDirY();
		_changeTimeDirY = 0.0f;
		_bCanChangeDirY = false;
	}
}

AttackReady::AttackReady(StateMachineComponent* stateMachine, GameObject* owner)
	:State(stateMachine, owner)
{
	_animComp = _owner->GetComponent<AnimatorComponent>();

	for (auto& obj : owner->GetScene()->GetObjects())
	{
		if (obj->GetTag() == L"Player")
		{
			_target = obj;
		}
		else if (obj->GetTag() == L"Monster" && obj != _owner)
		{
			_meteor = obj;
		}
	}
}

void AttackReady::Update()
{
	if (_animComp->GetCurAnim()->IsEnd())
	{
		_meteor->SetIsActive(true);
		_meteor->SetX(_target->GetX());
		_meteor->SetY(_target->GetY() - 500);

		ChangeState(eState::Idle);
	}
}

NormalAttack::NormalAttack(StateMachineComponent* stateMachine, GameObject* owner)
	:State(stateMachine, owner)
{
	_attackCollider = owner->GetComponent<AttackCollisionComponent>();
	_animComp = _owner->GetComponent<AnimatorComponent>();
}

void NormalAttack::Init()
{
	_attackCollider->Init();
}

void NormalAttack::Update()
{
	int curAnimationFrame = _animComp->GetCurAnim()->GetCurFrame();

	switch (curAnimationFrame)
	{
	case 3:
		_attackCollider->SetAttack({ 0,-35,122,15 }, 150, 0, 20.0f, 19.0f);
		break;
	case 5:
		_attackCollider->Init();
		break;
	}

	if (_animComp->GetCurAnim()->IsEnd())
	{
		ChangeState(eState::Idle);
	}
}

void NormalAttack::Release()
{
	_attackCollider->Init();
}
