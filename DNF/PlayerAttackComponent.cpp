#include "stdafx.h"
#include "PlayerAttackComponent.h"

#include "AnimatorComponent.h"

#include "Character.h"
#include "Player.h"

void PlayerAttackComponent::Update()
{
	Player* pOwner = (Player*)mpOwner;
	Character::eState	prevState = pOwner->GetState();
	Character::eDirX	prevDirX = pOwner->GetDirX();
	Player::eAttackType prevAtkType = pOwner->GetAttackType();
	AnimatorComponent* pAniComp = pOwner->GetComponent<AnimatorComponent>();
	int					currFrame = pAniComp->GetCurrFrame();

	if (Input::GetButton('0'))
	{
		pOwner->SetState(Player::eState::Damaged);
		return;
	}

	if (prevState == Character::eState::Idle
		|| prevState == Character::eState::Walk)
	{
		if (Input::GetButton('X'))
		{
			pOwner->SetState(Character::eState::Attack);
			pOwner->SetAttackType(Player::eAttackType::NormalAttack1);
			SetAnimation(L"NormalAttack1");

			return;
		}
	}
	else if (prevState == Character::eState::Run)
	{
		if (Input::GetButton('X'))
		{
			pOwner->SetState(Character::eState::Attack);
			pOwner->SetAttackType(Player::eAttackType::DashAttack1);
			SetAnimation(L"DashAttack1");

			return;
		}
	}
	else if (prevState == Character::eState::JumpWalk || prevState == Character::eState::JumpRun)
	{
		if (Input::GetButton('X'))
		{
			pOwner->SetState(Character::eState::JumpAttack);
			pOwner->SetAttackType(Player::eAttackType::JumpAttack);
			SetAnimation(L"JumpAttack");

			return;
		}
	}
	else if (prevState == Character::eState::Attack)
	{
		if (Input::GetButton('X'))
		{
			if (prevAtkType == Player::eAttackType::NormalAttack1)
			{
				if (currFrame >= 3)
				{
					pOwner->SetAttackType(Player::eAttackType::NormalAttack2);
					SetAnimation(L"NormalAttack2");
				}
			}
			else if (prevAtkType == Player::eAttackType::NormalAttack2)
			{
				if (currFrame >= 4)
				{
					pOwner->SetAttackType(Player::eAttackType::NormalAttack3);
					SetAnimation(L"NormalAttack3");
				}
			}
			else if (prevAtkType == Player::eAttackType::NormalAttack3)
			{
				if (currFrame >= 4)
				{
					pOwner->SetAttackType(Player::eAttackType::NormalAttack4);
					SetAnimation(L"NormalAttack4");
				}
			}
			else if (prevAtkType == Player::eAttackType::NormalAttack4)
			{
				if (currFrame >= 3)
				{
					pOwner->SetAttackType(Player::eAttackType::NormalAttack5);
					SetAnimation(L"NormalAttack5");
				}
			}
			else if (prevAtkType == Player::eAttackType::DashAttack1)
			{
				if (currFrame >= 4)
				{
					pOwner->SetAttackType(Player::eAttackType::DashAttack2);
					SetAnimation(L"DashAttack2");
				}
			}

			return;
		}
	}
	else if (prevState == Character::eState::JumpAttack)
	{
	}
}

void PlayerAttackComponent::SetAnimation(const wchar_t* tag)
{
	((Character*)mpOwner)->GetComponent<AnimatorComponent>()->Play(tag);
}