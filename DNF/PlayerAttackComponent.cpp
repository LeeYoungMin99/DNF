#include "stdafx.h"
#include "PlayerAttackComponent.h"

#include "GameObject.h"
#include "AnimatorComponent.h"
#include "Animation.h"

#include "AttackCollisionComponent.h"
#include "StateMachineComponent.h"

void PlayerAttackComponent::Init()
{
	_stateMachineComp = GetOwner()->GetComponent<StateMachineComponent>();
	_atkComp = GetOwner()->GetComponent<AttackCollisionComponent>();
	_animComp = GetOwner()->GetComponent<AnimatorComponent>();
}

void PlayerAttackComponent::Update()
{
	int curFrame = _animComp->GetCurAnim()->GetCurFrame();
	if (curFrame == 0) { _atkComp->Init(); }

	eState state = (eState)_stateMachineComp->GetCurStateTag();

	switch (state)
	{
	case eState::NormalAttack1:
		if (curFrame == 1) { SetAttack({ 0,-35, 200,15 }, 150, -25, 0.0f); };
		if (curFrame == 2) { if (curFrame != _prevFrame) _atkComp->ClearHitObjs(); }
		break;
	case eState::NormalAttack2:
		if (curFrame == 2) { SetAttack({ 0,-35, 200,15 }, 150, -25, 0.0f); };
		if (curFrame == 3) { if (curFrame != _prevFrame) _atkComp->ClearHitObjs(); }
		break;
	case eState::NormalAttack3:
		if (curFrame == 2) { SetAttack({ 0,-35, 200,15 }, 150, -25, 0.0f); };
		if (curFrame == 3) { if (curFrame != _prevFrame) _atkComp->ClearHitObjs(); }
		break;
	case eState::NormalAttack4:
		if (curFrame == 1) { SetAttack({ 0,-35, 200,15 }, 150, -25, 0.0f); };
		if (curFrame == 2) { if (curFrame != _prevFrame)  _atkComp->ClearHitObjs(); }
		break;
	case eState::NormalAttack5:
		if (curFrame == 1) { SetAttack({ 0,-35, 200,15 }, 150, -25, 0.0f); };
		if (curFrame == 2) { if (curFrame != _prevFrame) _atkComp->ClearHitObjs(); }
		break;
	case eState::JumpAttack:
		if (curFrame == 1) { SetAttack({ -130,-35,130,15 }, 200, -30, 0.0f); };
		if (curFrame == 2) { if (curFrame != _prevFrame) _atkComp->ClearHitObjs(); };
		if (curFrame == 3) { if (curFrame != _prevFrame) _atkComp->ClearHitObjs(); };
		if (curFrame == 4) { if (curFrame != _prevFrame) _atkComp->ClearHitObjs(); };
		break;
	case eState::DashAttack1:
		if (curFrame == 2) { SetAttack({ 0,-35, 200,15 }, 150, -25, 0.0f); };
		if (curFrame == 3) { if (curFrame != _prevFrame) _atkComp->ClearHitObjs(); }
		break;
	case eState::DashAttack2:
		if (curFrame == 2) { SetAttack({ 0,-35, 200,15 }, 150, -25, 0.0f); };
		if (curFrame == 3) { if (curFrame != _prevFrame) _atkComp->ClearHitObjs(); }
		break;
	case eState::Skill1:
		if (curFrame == 2) { SetAttack({ 0,-35, 180,15 }, 150, -25, 15.0f); };
		break;
	case eState::Skill2:
		if (curFrame == 3) { SetAttack({ 0,-35, 200,15 }, 150, -25, 0.0f); };
		if (curFrame == 8) { SetAttack({ 0,-35, 320,15 }, 150, -25, 0.0f); if (curFrame != _prevFrame) _atkComp->ClearHitObjs(); }
		if (curFrame == 12) { SetAttack({ 0,-35, 350,15 }, 150, -25, 15.0f, 6.0f); if (curFrame != _prevFrame) _atkComp->ClearHitObjs(); }
		break;
	default:
		_atkComp->Init();
		break;
	}

	_prevFrame = curFrame;
}

void PlayerAttackComponent::SetAttack(const RECT& size, int top, int bottom, float floatingPower, float resistance)
{
	_atkComp->SetAttack(size, top, bottom, floatingPower, resistance);
}