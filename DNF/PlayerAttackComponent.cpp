#include "stdafx.h"
#include "PlayerAttackComponent.h"

#include "GameObject.h"
#include "PlayerStatusComponent.h"
#include "AttackCollisionComponent.h"
#include "AnimatorComponent.h"
#include "Animation.h"

void PlayerAttackComponent::Init()
{
	_statusComp = _owner->GetComponent<PlayerStatusComponent>();
	_atkComp = _owner->GetComponent<AttackCollisionComponent>();
	_animComp = _owner->GetComponent<AnimatorComponent>();
}

void PlayerAttackComponent::Update()
{
	using state = PlayerStatusComponent::ePlayerState;

	int currFrame = _animComp->GetCurAnim()->GetCurrFrame();
	if (currFrame == 0) { _atkComp->Init(); }

	switch (_statusComp->GetState())
	{
	case state::NormalAttack1:
		if (currFrame == 1) { SetAttack({ 0,-35, 200,15 }, -150, 25, 0.0f); };
		if (currFrame == 2) { _atkComp->ClearHitObjs(); }
		break;
	case state::NormalAttack2:
		if (currFrame == 2) { SetAttack({ 0,-35, 200,15 }, -150, 25, 0.0f); };
		if (currFrame == 3) { _atkComp->ClearHitObjs(); }
		break;
	case state::NormalAttack3:
		if (currFrame == 2) { SetAttack({ 0,-35, 200,15 }, -150, 25, 0.0f); };
		if (currFrame == 3) { _atkComp->ClearHitObjs(); }
		break;
	case state::NormalAttack4:
		if (currFrame == 1) { SetAttack({ 0,-35, 200,15 }, -150, 25, 0.0f); };
		if (currFrame == 2) { _atkComp->ClearHitObjs(); }
		break;
	case state::NormalAttackEnd:
		if (currFrame == 1) { SetAttack({ 0,-35, 200,15 }, -150, 25, 0.0f); };
		if (currFrame == 2) { _atkComp->ClearHitObjs(); }
		break;
	case state::JumpAttack:
		if (currFrame == 1) { SetAttack({ -130,-35,130,15 }, -200, 30, 0.0f); };
		if (currFrame == 2) { _atkComp->ClearHitObjs(); };
		if (currFrame == 3) { _atkComp->ClearHitObjs(); };
		if (currFrame == 4) { _atkComp->ClearHitObjs(); };
		break;
	case state::DashAttackStart:
		if (currFrame == 2) { SetAttack({ 0,-35, 200,15 }, -150, 25, 0.0f); };
		if (currFrame == 3) { _atkComp->ClearHitObjs(); }
		break;
	case state::DashAttackEnd:
		if (currFrame == 2) { SetAttack({ 0,-35, 200,15 }, -150, 25, 0.0f); };
		if (currFrame == 3) { _atkComp->ClearHitObjs(); }
		break;
	case state::UpperSlash:
		if (currFrame == 2) { SetAttack({ 0,-35, 180,15 }, -150, 25, 15.0f); };
		break;
	case state::SnakeDance:
		if (currFrame == 3) { SetAttack({ 0,-35, 200,15 }, -150, 25, 0.0f); };
		if (currFrame == 8) { SetAttack({ 0,-35, 320,15 }, -150, 25, 0.0f); _atkComp->ClearHitObjs(); }
		if (currFrame == 12) { SetAttack({ 0,-35, 350,15 }, -150, 25, 0.0f); _atkComp->ClearHitObjs(); }
		break;
	default:
		_atkComp->Init();
		break;
	}
}

void PlayerAttackComponent::SetAttack(const RECT& size, int top, int bottom, float floatingPower)
{
	_atkComp->SetAttack(size, top, bottom, floatingPower);
}
