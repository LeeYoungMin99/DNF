#include "stdafx.h"
#include "PlayerState.h"

#include "StateMachineComponent.h"
#include "TransformComponent.h"
#include "PositionComponent.h"
#include "AnimatorComponent.h"
#include "Animation.h"

#include "GameObject.h"

void PlayerState::ChangeState(eState state)
{
	_stateMachineComp->ChangeState((int)state);
}

void PlayerState::ChangeState(int stateTag)
{
	_stateMachineComp->ChangeState(stateTag);
}

PlayerAction::PlayerAction(StateMachineComponent* stateMachine, GameObject* owner)
	:PlayerState(stateMachine, owner)
{
	_animComp = owner->GetComponent<AnimatorComponent>();
}

void PlayerAction::Update()
{
	if (IsEndAnimation()) { ChangeState(eState::Idle); }
}

bool PlayerAction::IsEndAnimation()
{
	return _animComp->GetCurAnim()->IsEnd();
}

void PlayerIdle::Update()
{
	if (Input::GetButtonDown(PLAYER_SKILL_QUICK_SLOT_1_KEY)) { ChangeState(eState::Skill2); }
	else if (InputPlayerAttackKey()) { ChangeState(eState::NormalAttack1); }
	else if (InputPlayerJumpKey()) { ChangeState(eState::Jump);}

	else if (InputPlayerMoveKey()) { ChangeState(eState::Walk); }
}

void PlayerWalk::Update()
{
	if (Input::GetButtonDown(PLAYER_SKILL_QUICK_SLOT_1_KEY)) { ChangeState(eState::Skill2); }
	else if (Input::GetButtonDown(PLAYER_ATTACK_KEY)) { ChangeState(eState::NormalAttack1); }
	else if (Input::GetButtonDown(PLAYER_JUMP_KEY)) { ChangeState(eState::Jump); }

	else if (false == InputPlayerMoveKey()) { ChangeState(eState::Idle); }
}

PlayerRun::PlayerRun(StateMachineComponent* stateMachine, GameObject* owner)
	:PlayerState(stateMachine, owner)
{
	_transformComp = owner->GetComponent<TransformComponent>();
}

void PlayerRun::Update()
{
	using eDirX = TransformComponent::eDirX;
	eDirX dirX = _transformComp->GetDirX();

	if (Input::GetButtonDown(PLAYER_SKILL_QUICK_SLOT_1_KEY)) { ChangeState(eState::Skill2); return; }
	if (Input::GetButtonDown(PLAYER_ATTACK_KEY)) { ChangeState(eState::DashAttack1); return; }
	if (Input::GetButtonDown(PLAYER_JUMP_KEY)) { ChangeState(eState::Jump); return; }

	else if (eDirX::Left == dirX)
	{
		if (false == (Input::GetButton(PLAYER_UP_MOVE_KEY) || Input::GetButton(PLAYER_DOWN_MOVE_KEY)))
		{
			if (Input::GetButtonUp(PLAYER_LEFT_MOVE_KEY)) { ChangeState(eState::Idle); return; }
		}

		if (Input::GetButtonDown(PLAYER_RIGHT_MOVE_KEY)) { ChangeState(eState::Walk); return; }
	}
	else if (eDirX::Right == dirX)
	{
		if (false == (Input::GetButton(PLAYER_UP_MOVE_KEY) || Input::GetButton(PLAYER_DOWN_MOVE_KEY)))
		{
			if (Input::GetButtonUp(PLAYER_RIGHT_MOVE_KEY)) { ChangeState(eState::Idle); return; }
		}

		if (Input::GetButtonDown(PLAYER_LEFT_MOVE_KEY)) { ChangeState(eState::Walk); return; }
	}

	if (false == InputPlayerMoveKey()) { ChangeState(eState::Idle);}
}

PlayerJump::PlayerJump(StateMachineComponent* stateMachine, GameObject* owner)
	:PlayerState(stateMachine, owner)
{
	_posComp = owner->GetComponent<PositionComponent>();
}

void PlayerJump::Init()
{
	_posComp->SetAcceleration(20.0f);
}

void PlayerJump::Update()
{
	if (_posComp->GetZ() <= 0) { ChangeState(eState::JumpDownIdle); }
	else if (InputPlayerAttackKey()) { ChangeState(eState::JumpAttack); }
}

PlayerJumpAttack::PlayerJumpAttack(StateMachineComponent* stateMachine, GameObject* owner)
	:PlayerState(stateMachine, owner)
{
	_posComp = owner->GetComponent<PositionComponent>();
}

void PlayerJumpAttack::Update()
{
	if (_posComp->GetZ() <= 0) { ChangeState(eState::JumpDownIdle); }
}

void PlayerAttack::Init()
{
	_bInputCombo = false;
	_elapsedTime = 0.0f;
}

void PlayerAttack::Update()
{
	eState state = (eState)_stateMachineComp->GetCurStateTag();
	_elapsedTime += Timer::GetDeltaTime();

	if (Input::GetButtonDown(PLAYER_SKILL_QUICK_SLOT_1_KEY))
	{
		if (state != eState::DashAttack1 && state != eState::DashAttack2)
		{
			 ChangeState(eState::Skill2);
		}
	}
	else if (InputPlayerAttackKey())
	{
		if (CAN_INPUT_ELAPSED_TIME <= _elapsedTime)
		{
			_bInputCombo = true;
		}
	}
	
	if (IsEndAnimation()) { ChangeState(eState::Idle); }
	else if (state != eState::NormalAttack5 && state != eState::DashAttack2)
	{
		if (CheckCanCombo())
		{
			ChangeState((_stateMachineComp->GetCurStateTag() + NEXT_STATE));
		}
	}
		
}

bool PlayerAttack::CheckCanCombo()
{
	return _animComp->GetCurAnim()->CanCancel() && _bInputCombo;
}
