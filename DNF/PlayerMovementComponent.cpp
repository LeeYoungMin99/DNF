#include "stdafx.h"
#include "PlayerMovementComponent.h"

#include "GameObject.h"
#include "PlayerStatusComponent.h"
#include "PlayerTransformComponent.h"

void PlayerMovementComponent::Init()
{
	_statusComp = _owner->GetComponent<PlayerStatusComponent>();
	_transformComp = _owner->GetComponent<PlayerTransformComponent>();
}

void PlayerMovementComponent::Update()
{
	switch (_statusComp->GetState())
	{
	case PlayerStatusComponent::ePlayerState::Walk:
		_moveSpeed = WALK_SPEED;
		break;
	case PlayerStatusComponent::ePlayerState::Run:
		_moveSpeed = RUN_SPEED;
		break;
	case PlayerStatusComponent::ePlayerState::Jump:
	case PlayerStatusComponent::ePlayerState::JumpAttack:
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