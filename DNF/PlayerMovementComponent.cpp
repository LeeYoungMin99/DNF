#include "stdafx.h"
#include "PlayerMovementComponent.h"

#include "GameObject.h"
#include "StateMachineComponent.h"
#include "PlayerTransformComponent.h"

void PlayerMovementComponent::Init()
{
	_statusComp = _owner->GetComponent<StateMachineComponent>();
	_transformComp = _owner->GetComponent<PlayerTransformComponent>();
}

void PlayerMovementComponent::Update()
{
	eState state = (eState)_statusComp->GetCurStateTag();

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
	PlayerTransformComponent::eDirX dirX = _transformComp->GetDirX();
	PlayerTransformComponent::eDirY dirY = _transformComp->GetDirY();

	if (Input::GetButton(VK_LEFT))
	{
		if (PlayerTransformComponent::eDirX::Left == dirX)
		{
			_owner->AddX((LONG)-(_moveSpeed * deltaTime));
		}
	}
	
	if (Input::GetButton(VK_RIGHT))
	{
		if (PlayerTransformComponent::eDirX::Right == dirX)
		{
			_owner->AddX((LONG)(_moveSpeed * deltaTime));
		}
	}

	if (Input::GetButton(VK_UP))
	{
		if (PlayerTransformComponent::eDirY::Up == dirY)
		{
			_owner->AddY((LONG)-(Y_SPEED * deltaTime));
		}
	}
	
	if (Input::GetButton(VK_DOWN))
	{
		if (PlayerTransformComponent::eDirY::Down == dirY)
		{
			_owner->AddY((LONG)(Y_SPEED * deltaTime));
		}
	}
}