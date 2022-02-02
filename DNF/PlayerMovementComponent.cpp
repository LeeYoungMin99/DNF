#include "stdafx.h"
#include "PlayerMovementComponent.h"

#include "GameObject.h"
#include "StateMachineComponent.h"
#include "PlayerTransformComponent.h"

void PlayerMovementComponent::Init()
{
	_stateMachineComp = GetOwner()->GetComponent<StateMachineComponent>();
	_transformComp = GetOwner()->GetComponent<PlayerTransformComponent>();
}

void PlayerMovementComponent::Update()
{
	eState state = (eState)_stateMachineComp->GetCurStateTag();

	switch (state)
	{
	case eState::Walk:
		_moveSpeed = WALK_SPEED;
		break;
	case eState::Run:
		_moveSpeed = RUN_SPEED;
		break;
	case eState::Jump:
	case eState::JumpAttack:
		break;
	default:
		return;
	}

	Move();
}

void PlayerMovementComponent::Move()
{
	float deltaTime = Timer::GetDeltaTime();
	eDirX dirX = _transformComp->GetDirX();
	eDirY dirY = _transformComp->GetDirY();

	if (Input::GetButton(VK_LEFT))
	{
		if (eDirX::Left == dirX)
		{
			GetOwner()->AddX((LONG)-(_moveSpeed * deltaTime));
		}
	}
	
	if (Input::GetButton(VK_RIGHT))
	{
		if (eDirX::Right == dirX)
		{
			GetOwner()->AddX((LONG)(_moveSpeed * deltaTime));
		}
	}

	if (Input::GetButton(VK_UP))
	{
		if (eDirY::Up == dirY)
		{
			GetOwner()->AddY((LONG)-(Y_SPEED * deltaTime));
		}
	}
	
	if (Input::GetButton(VK_DOWN))
	{
		if (eDirY::Down == dirY)
		{
			GetOwner()->AddY((LONG)(Y_SPEED * deltaTime));
		}
	}
}