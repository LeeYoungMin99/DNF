#include "stdafx.h"
#include "PlayerStatusComponent.h"

#include "GameObject.h"
#include "Animation.h"
#include "AnimatorComponent.h"
#include "PlayerTransformComponent.h"

#include "PositionComponent.h"

void PlayerStatusComponent::Init()
{
	_animComp = _owner->GetComponent<AnimatorComponent>();
	_transformComp = _owner->GetComponent<PlayerTransformComponent>();
	_posComp = _owner->GetComponent<PositionComponent>();
}

void PlayerStatusComponent::Update()
{
	_elapsedStateChangeTime += Timer::GetDeltaTime();

	using eDirX = PlayerTransformComponent::eDirX;
	eDirX dirX = _transformComp->GetDirX();

	switch (_state)
	{
	case ePlayerState::Idle:
		if (CheckSkill_1()) { break; }
		if (StartNormalAttack()) { break; }
		if (Jump()) { break; }
		if (InputArrowKeys()) { SetState(ePlayerState::Walk); break; }
		break;

	case ePlayerState::Walk:
		if (CheckSkill_1()) { break; }
		if (StartNormalAttack()) { break; }
		if (Jump()) { break; }
		if (InputArrowKeys()) { break; }
		else { SetState(ePlayerState::Idle); break; }
		break;

	case ePlayerState::Run:
		if (CheckSkill_1()) { break; }
		if (Input::GetButtonDown('X')) { _state = ePlayerState::DashAttackStart; InitElapsedTime();  break; }

		if (eDirX::Left == dirX)
		{
			if (false == (Input::GetButton(VK_UP) || Input::GetButton(VK_DOWN)))
			{
				if (Input::GetButtonUp(VK_LEFT)) { SetState(ePlayerState::Idle); break; }
			}

			if (Input::GetButtonDown(VK_RIGHT)) { SetState(ePlayerState::Walk); break; }
		}
		else if (eDirX::Right == dirX)
		{
			if (false == (Input::GetButton(VK_UP) || Input::GetButton(VK_DOWN)))
			{
				if (Input::GetButtonUp(VK_RIGHT)) { SetState(ePlayerState::Idle); break; }
			}

			if (Input::GetButtonDown(VK_LEFT)) { SetState(ePlayerState::Walk); break; }
		}

		if (Jump()) { break; }
		if (InputArrowKeys()) { break; }
		else { SetState(ePlayerState::Idle); break; }
		break;

	case ePlayerState::Jump:
		if (Input::GetButtonDown('X')) { SetState(ePlayerState::JumpAttack); }
	case ePlayerState::JumpAttack:
		if (_posComp->GetZ() <= 0) { SetState(ePlayerState::JumpDownIdle); }
		break;

	case ePlayerState::JumpDownIdle:
		CheckCanChangeIdle();
		break;

	case ePlayerState::NormalAttack1:
	case ePlayerState::NormalAttack2:
	case ePlayerState::NormalAttack3:
	case ePlayerState::NormalAttack4:
		// 다음 콤보로 이어지는건 1234만 가능함.
		CheckCanCombo();
		if (CheckNextState()) { break; }

	case ePlayerState::NormalAttackEnd:
		if (CheckSkill_1()) { break; }

		CheckCanChangeIdle();
		break;

	case ePlayerState::DashAttackStart:
		CheckCanCombo();
		if (CheckNextState()) { break; }

	case ePlayerState::DashAttackEnd:
	case ePlayerState::UpperSlash:
	case ePlayerState::SnakeDance:
		CheckCanChangeIdle();
		break;

	}
}

bool PlayerStatusComponent::StartNormalAttack()
{
	if (Input::GetButtonDown('X'))
	{
		SetState(ePlayerState::NormalAttack1);
		InitElapsedTime();
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerStatusComponent::CheckSkill_1()
{
	if (Input::GetButtonDown('A'))
	{
		SetState(ePlayerState::SnakeDance);

		return true;
	}

	return false;
}

bool PlayerStatusComponent::Jump()
{
	if (Input::GetButtonDown('C'))
	{
		_posComp->SetAcceleration(20.0f);
		SetState(ePlayerState::Jump);
		return true;
	}

	return false;
}

bool PlayerStatusComponent::CheckNextState()
{
	if (_animComp->GetCurAnim()->CanCancel())
	{
		if (_nextState != ePlayerState::Idle)
		{
			SetState(_nextState);
			SetNextState(ePlayerState::Idle);
			InitElapsedTime();
			return true;
		}
	}

	return false;
}

void PlayerStatusComponent::CheckCanChangeIdle()
{
	if (_animComp->GetCurAnim()->IsEnd())
	{
		SetState(ePlayerState::Idle);
	}
}

void PlayerStatusComponent::CheckCanCombo()
{
	if (_elapsedStateChangeTime >= CAN_COMBO_INPUT)
	{
		if (Input::GetButtonDown('X'))
		{
			SetNextState((ePlayerState)((int)_state + 1));
		}
	}
}
