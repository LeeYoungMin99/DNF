#include "stdafx.h"
#include "PlayerMovementComponent.h"

#include "AnimatorComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "Player.h"
#include "Character.h"

void PlayerMovementComponent::Update()
{
	float deltaTime = Timer::GetDeltaTime();
	mInputTime += deltaTime;

	Player* pOwner = (Player*)mpOwner;
	AnimatorComponent* pAniComp = pOwner->GetComponent<AnimatorComponent>();
	Player::eState		prevState = pOwner->GetState();
	Player::eDirX		prevDirX = pOwner->GetDirX();

	if (prevState == Player::eState::Attack || prevState == Player::eState::Damaged)
	{
		return;
	}

	if (prevState != Player::eState::JumpWalk
		&& prevState != Player::eState::JumpRun
		&& prevState != Player::eState::JumpAttack)
	{
		pOwner->SetAttackType(Player::eAttackType::None);
		if (false == (Input::GetButton(VK_LEFT) || Input::GetButtonDown(VK_LEFT)) &&
			false == (Input::GetButton(VK_RIGHT) || Input::GetButtonDown(VK_RIGHT)) &&
			false == (Input::GetButton(VK_UP) || Input::GetButtonDown(VK_UP)) &&
			false == (Input::GetButton(VK_DOWN) || Input::GetButtonDown(VK_DOWN)) &&
			false == Input::GetButtonDown('C'))
		{
			if (prevState == Player::eState::Idle) { return; }
			else
			{
				pOwner->SetState(Player::eState::Idle);
				SetAnimation(L"Idle");
				return;
			}
		}

		if (Input::GetButtonDown('C'))
		{
			if (prevState == Player::eState::Run)
			{
				pOwner->SetState(Player::eState::JumpRun);
			}
			else
			{
				pOwner->SetState(Player::eState::JumpWalk);
			}

			SetAnimation(L"Jump");

			float jumpAccel = 14.0f;
			pOwner->SetAcceleration(jumpAccel);
			pOwner->SetResistance(jumpAccel * 2);
			mInputTime = 0.0f;
			return;
		}

		if (Input::GetButtonDown(VK_LEFT))
		{
			if (mInputTime >= 0.4f)
			{
				if (prevState == Player::eState::Run && prevDirX == Player::eDirX::Left)
				{
					pOwner->SetState(Player::eState::Run);
				}
				else
				{
					pOwner->SetState(Player::eState::Walk);
				}
			}
			else
			{
				if (mPrevKey == (int)Player::eDirX::Left)
				{
					pOwner->SetState(Player::eState::Run);
				}
			}

			pOwner->SetDirX(Player::eDirX::Left);
			mPrevKey = (int)Player::eDirX::Left;
			mInputTime = 0.0f;
		}
		else if (Input::GetButtonDown(VK_RIGHT))
		{
			if (mInputTime >= 0.4f)
			{
				if (prevState == Player::eState::Run && prevDirX == Player::eDirX::Right)
				{
					pOwner->SetState(Player::eState::Run);
				}
				else
				{
					pOwner->SetState(Player::eState::Walk);
				}
			}
			else
			{
				if (mPrevKey == (int)Player::eDirX::Right)
				{
					pOwner->SetState(Player::eState::Run);
				}
			}

			pOwner->SetDirX(Player::eDirX::Right);
			mPrevKey = (int)Player::eDirX::Right;
			mInputTime = 0.0f;
		}

		if (Input::GetButtonDown(VK_UP))
		{
			pOwner->SetDirY(Player::eDirY::Up);
		}
		else if (Input::GetButtonDown(VK_DOWN))
		{
			pOwner->SetDirY(Player::eDirY::Down);
		}

		if (prevState == Player::eState::Idle)
		{
			if (Input::GetButton(VK_LEFT))
			{
				pOwner->SetDirX(Player::eDirX::Left);
				pOwner->SetState(Player::eState::Walk);
			}
			else if (Input::GetButton(VK_RIGHT))
			{
				pOwner->SetDirX(Player::eDirX::Right);
				pOwner->SetState(Player::eState::Walk);
			}

			if (Input::GetButton(VK_UP))
			{
				pOwner->SetDirY(Player::eDirY::Up);
				pOwner->SetState(Player::eState::Walk);
			}
			else if (Input::GetButton(VK_DOWN))
			{
				pOwner->SetDirY(Player::eDirY::Down);
				pOwner->SetState(Player::eState::Walk);
			}
		}
		else
		{
			if (Input::GetButtonUp(VK_LEFT) && Input::GetButton(VK_RIGHT))
			{
				pOwner->SetState(Player::eState::Walk);
				pOwner->SetDirX(Player::eDirX::Right);
			}
			else if (Input::GetButtonUp(VK_RIGHT) && Input::GetButton(VK_LEFT))
			{
				pOwner->SetState(Player::eState::Walk);
				pOwner->SetDirX(Player::eDirX::Left);
			}

			if (Input::GetButtonUp(VK_UP) && Input::GetButton(VK_DOWN))
			{
				pOwner->SetDirY(Player::eDirY::Down);
			}
			else if (Input::GetButtonUp(VK_DOWN) && Input::GetButton(VK_UP))
			{
				pOwner->SetDirY(Player::eDirY::Up);
			}
		}
	}
	else
	{
		float accel = pOwner->GetAcceleration();
		float resist = pOwner->GetResistance();

		pOwner->AddZ((int)(accel - (resist * 0.8f * mInputTime)));

		if (pOwner->GetZ() <= 0)
		{
			pOwner->SetZ(0);
			pOwner->SetState(Player::eState::Idle);

			if (pAniComp->GetCurrSpriteTag() == L"LeftJumpAttack")
			{
				pOwner->SetDirX(Player::eDirX::Left);
			}
			else if (pAniComp->GetCurrSpriteTag() == L"RightJumpAttack")
			{
				pOwner->SetDirX(Player::eDirX::Right);
			}

			SetAnimation(L"JumpDownIdle");
			return;
		}

		if (Input::GetButtonDown(VK_LEFT))
		{
			pOwner->SetDirX(Player::eDirX::Left);
			mPrevKey = (int)Player::eDirX::Left;
		}
		else if (Input::GetButtonDown(VK_RIGHT))
		{
			pOwner->SetDirX(Player::eDirX::Right);
			mPrevKey = (int)Player::eDirX::Right;
		}

		if (Input::GetButton(VK_LEFT) && Input::GetButton(VK_RIGHT))
		{
			pOwner->SetDirX((Player::eDirX)mPrevKey);
		}
		else if (Input::GetButton(VK_LEFT)) { pOwner->SetDirX(Player::eDirX::Left); }
		else if (Input::GetButton(VK_RIGHT)) { pOwner->SetDirX(Player::eDirX::Right); }

		if (Input::GetButton(VK_UP)) { pOwner->SetDirY(Player::eDirY::Up); }
		else if (Input::GetButton(VK_DOWN)) { pOwner->SetDirY(Player::eDirY::Down); }
	}

	Player::eState	state = pOwner->GetState();
	Player::eDirX	dirX = pOwner->GetDirX();
	Player::eDirY	dirY = pOwner->GetDirY();

	if (prevState != state)
	{
		if (state == Player::eState::Walk)
		{
			SetAnimation(L"Walk");
		}
		else if (state == Player::eState::Run)
		{
			SetAnimation(L"Run");
		}
		else
		{
			SetAnimation(L"Jump");
		}
	}
	Move((int)state, (int)dirX, (int)dirY, deltaTime);
}

void PlayerMovementComponent::SetAnimation(const wchar_t* tag)
{
	((Player*)mpOwner)->GetComponent<AnimatorComponent>()->Play(tag);
}

void PlayerMovementComponent::Move(int state, int dirX, int dirY, float deltaTime) noexcept
{
	int moveSpeed = ((Player*)mpOwner)->GetMoveSpeed();

	if (state == (int)Player::eState::JumpAttack)
		state = 1;

	if (state > 2)
		state -= 2;

	if (Input::GetButton(VK_LEFT) || Input::GetButton(VK_RIGHT))
	{
		mpOwner->AddX((LONG)((moveSpeed * deltaTime) * dirX * state));
	}

	if (Input::GetButton(VK_UP) || Input::GetButton(VK_DOWN))
	{
		mpOwner->AddY((LONG)((moveSpeed * deltaTime) * dirY));
	}
}
