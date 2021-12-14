#include "stdafx.h"
#include "PlayerAttackComponent.h"

#include "AnimatorComponent.h"

#include "Character.h"
#include "Player.h"

void PlayerAttackComponent::Update()
{
	Character::eState	prevState = ((Character*)mpOwner)->GetState();
	Character::eDirX	prevDirX = ((Character*)mpOwner)->GetDirX();
	Player::eAttackType prevAtkType = ((Player*)mpOwner)->GetAttackType();
	AnimatorComponent*	pAniComp = mpOwner->GetComponent<AnimatorComponent>();
	int					currFrame = pAniComp->mCurrFrame;

	if (Input::GetButton('0'))
	{
		((Player*)mpOwner)->SetState(Player::eState::Damaged);
		return;
	}

	if (prevState == Character::eState::Idle
		|| prevState == Character::eState::Walk)
	{
		if (Input::GetButton('X'))
		{
			((Character*)mpOwner)->SetState(Character::eState::Attack);
			((Player*)mpOwner)->SetAttackType(Player::eAttackType::NormalAttack1);
			SetAnimation(L"NormalAttack1");

			return;
		}
	}
	else if (prevState == Character::eState::Run)
	{
		if (Input::GetButton('X'))
		{
			((Character*)mpOwner)->SetState(Character::eState::Attack);
			((Player*)mpOwner)->SetAttackType(Player::eAttackType::DashAttack1);
			SetAnimation(L"DashAttack1");

			return;
		}
	}
	else if (prevState == Character::eState::JumpWalk || prevState == Character::eState::JumpRun)
	{
		if (Input::GetButton('X'))
		{
			((Character*)mpOwner)->SetState(Character::eState::JumpAttack);
			((Player*)mpOwner)->SetAttackType(Player::eAttackType::JumpAttack);
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
					((Player*)mpOwner)->SetAttackType(Player::eAttackType::NormalAttack2);
					SetAnimation(L"NormalAttack2");
				}
			}
			else if (prevAtkType == Player::eAttackType::NormalAttack2)
			{
				if (currFrame >= 4)
				{
					((Player*)mpOwner)->SetAttackType(Player::eAttackType::NormalAttack3);
					SetAnimation(L"NormalAttack3");
				}
			}
			else if (prevAtkType == Player::eAttackType::NormalAttack3)
			{
				if (currFrame >= 4)
				{
					((Player*)mpOwner)->SetAttackType(Player::eAttackType::NormalAttack4);
					SetAnimation(L"NormalAttack4");
				}
			}
			else if (prevAtkType == Player::eAttackType::NormalAttack4)
			{
				if (currFrame >= 3)
				{
					((Player*)mpOwner)->SetAttackType(Player::eAttackType::NormalAttack5);
					SetAnimation(L"NormalAttack5");
				}
			}
			else if (prevAtkType == Player::eAttackType::DashAttack1)
			{
				if (currFrame >= 4)
				{
					((Player*)mpOwner)->SetAttackType(Player::eAttackType::DashAttack2);
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
	wchar_t left[50] = {};
	wchar_t right[50] = {};

	wsprintfW(left, L"Left%s", tag);
	wsprintfW(right, L"Right%s", tag);

	if (((Character*)mpOwner)->GetDirX() == Character::eDirX::Left)
	{
		((Character*)mpOwner)->GetComponent<AnimatorComponent>()->Play(left);
	}
	else
	{
		((Character*)mpOwner)->GetComponent<AnimatorComponent>()->Play(right);
	}
}