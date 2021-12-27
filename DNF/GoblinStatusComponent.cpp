#include "stdafx.h"
#include "GoblinStatusComponent.h"

#include "GameObject.h"

#include "PositionComponent.h"
#include "AnimatorComponent.h"
#include "Animation.h"

void GoblinStatusComponent::Init()
{
	_posComp = _owner->GetComponent<PositionComponent>();
	_animComp = _owner->GetComponent<AnimatorComponent>();
}

void GoblinStatusComponent::Update()
{
	switch (_state)
	{
	case eGoblinState::Idle:
		break;
	case eGoblinState::Damaged:
		if (_posComp->GetZ() > 0) { SetState(eGoblinState::JumpDamaged); }
		else if (_animComp->GetCurAnim()->IsEnd()) { SetState(eGoblinState::Idle); }
		break;
	case eGoblinState::JumpDamaged:
		if (_posComp->GetZ() <= 0) 
		{ 
			SetState(eGoblinState::JumpDownIdle); 
		}
		break;
	case eGoblinState::JumpDownIdle:
		if (_animComp->GetCurAnim()->IsEnd()) { SetState(eGoblinState::Idle); }
		break;
	default:
		break;
	}
}
