#include "stdafx.h"
#include "PlayerAttackComponent.h"

#include "AnimatorComponent.h"

#include "Character.h"
#include "Player.h"

void PlayerAttackComponent::Update()
{
	Player* pOwner = (Player*)mpOwner;
	Player::eState	prevState = pOwner->GetState();
	Player::eDirX	prevDirX = pOwner->GetDirX();
	Player::eAttackType prevAtkType = pOwner->GetAttackType();
	AnimatorComponent* pAniComp = pOwner->GetComponent<AnimatorComponent>();
	int					currFrame = pAniComp->GetCurrFrame();

	switch (prevState)
	{
	case Player::eState::Idle:
	case Player::eState::Walk:
		if (Input::GetButton('X'))
		{
			pOwner->SetState(Character::eState::Attack);
			pOwner->SetAttackType(Player::eAttackType::NormalAttack1);
			SetAnimation(L"NormalAttack1");
		}
		else if (Input::GetButtonDown('A'))
		{
			pOwner->SetState(Character::eState::Attack);
			pOwner->SetAttackType(Player::eAttackType::SnakeDance);
			SetAnimation(L"SnakeDance");
		}
		break;
	case Player::eState::Run:
		if (Input::GetButton('X'))
		{
			pOwner->SetState(Character::eState::Attack);
			pOwner->SetAttackType(Player::eAttackType::DashAttack1);
			SetAnimation(L"DashAttack1");
		}
		else if (Input::GetButtonDown('A'))
		{
			pOwner->SetState(Character::eState::Attack);
			pOwner->SetAttackType(Player::eAttackType::SnakeDance);
			SetAnimation(L"SnakeDance");
		}
		break;
	case Player::eState::JumpWalk:
	case Player::eState::JumpRun:
		if (Input::GetButton('X'))
		{
			pOwner->SetState(Character::eState::JumpAttack);
			pOwner->SetAttackType(Player::eAttackType::JumpAttack);
			SetAnimation(L"JumpAttack");
		}
		break;
	case Player::eState::JumpAttack:
		break;
	case Player::eState::Attack:
		if (prevAtkType == Player::eAttackType::NormalAttack1)
		{
			if (currFrame == 0)
			{
				pOwner->SetAttackHitbox(0.5f, 0.0f, { -120,-25,262,5 });
			}
			else if (currFrame == 4)
			{
				pOwner->InitAttackHitbox();
			}

			if (currFrame >= 4)
			{
				if (Input::GetButton('X'))
				{
					pOwner->InitAttackHitbox();
					pOwner->SetAttackType(Player::eAttackType::NormalAttack2);
					SetAnimation(L"NormalAttack2");
				}
			}
		}
		else if (prevAtkType == Player::eAttackType::NormalAttack2)
		{
			if (currFrame == 0)
			{
				pOwner->SetAttackHitbox(0.5f, 0.0f, { -24,-25,263,5 });
			}
			else if (currFrame == 5)
			{
				pOwner->InitAttackHitbox();
			}

			if (currFrame >= 4)
			{
				if (Input::GetButton('X'))
				{
					pOwner->InitAttackHitbox();
					pOwner->SetAttackType(Player::eAttackType::NormalAttack3);
					SetAnimation(L"NormalAttack3");
				}
			}
		}
		else if (prevAtkType == Player::eAttackType::NormalAttack3)
		{
			if (currFrame == 0)
			{
				pOwner->SetAttackHitbox(0.5f, 0.0f, { -120,-25,265,5 });
			}
			else if (currFrame == 5)
			{
				pOwner->InitAttackHitbox();
			}

			if (currFrame >= 4)
			{
				if (Input::GetButton('X'))
				{
					pOwner->InitAttackHitbox();
					pOwner->SetAttackType(Player::eAttackType::NormalAttack4);
					SetAnimation(L"NormalAttack4");
				}
			}
		}
		else if (prevAtkType == Player::eAttackType::NormalAttack4)
		{
			if (currFrame == 0)
			{
				pOwner->SetAttackHitbox(0.5f, 0.0f, { -150,-25,280,5 });
			}
			else if (currFrame == 4)
			{
				pOwner->InitAttackHitbox();
			}

			if (currFrame >= 4)
			{
				if (Input::GetButton('X'))
				{
					pOwner->InitAttackHitbox();
					pOwner->SetAttackType(Player::eAttackType::NormalAttack5);
					SetAnimation(L"NormalAttack5");
				}
			}
		}
		else if (prevAtkType == Player::eAttackType::NormalAttack5)
		{
			if (currFrame == 0)
			{
				pOwner->SetAttackHitbox(0.5f, 0.0f, { -60,-25,280,5 });
			}
			else if (currFrame == 4)
			{
				pOwner->InitAttackHitbox();
			}
		}
		else if (prevAtkType == Player::eAttackType::DashAttack1)
		{
			if (currFrame == 0)
			{
				pOwner->SetAttackHitbox(0.5f, 0.0f, { -24,-25,263,5 });
			}
			else if (currFrame == 5)
			{
				pOwner->InitAttackHitbox();
			}

			if (currFrame >= 4)
			{
				if (Input::GetButton('X'))
				{
					pOwner->InitAttackHitbox();
					pOwner->SetAttackType(Player::eAttackType::DashAttack2);
					SetAnimation(L"DashAttack2");
				}
			}
		}
		else if (prevAtkType == Player::eAttackType::DashAttack2)
		{
			if (currFrame == 0)
			{
				pOwner->SetAttackHitbox(0.5f, 0.0f, { -65,-25,255,5 });
			}
			else if (currFrame == 5)
			{
				pOwner->InitAttackHitbox();
			}
		}
		else if (prevAtkType == Player::eAttackType::SnakeDance)
		{
			if (currFrame == 2)
			{
				pOwner->SetAttackHitbox(0.5f, 0.0f, { -140,-35,245,15 });
			}
			else if (currFrame == 6)
			{
				pOwner->InitAttackHitbox();
			}
			else if (currFrame == 8)
			{
				pOwner->SetAttackHitbox(0.5f, 0.0f, { -140,-35,400,15 });
			}
			else if (currFrame == 11)
			{
				pOwner->InitAttackHitbox();
			}
			else if (currFrame == 12)
			{
				pOwner->SetAttackHitbox(0.5f, 0.0f, { -140,-35,460,15 });
			}
			else if (currFrame == 16)
			{
				pOwner->InitAttackHitbox();
			}
		}
		break;
	}
}

void PlayerAttackComponent::SetAnimation(const wchar_t* tag)
{
	((Character*)mpOwner)->GetComponent<AnimatorComponent>()->Play(tag);
}