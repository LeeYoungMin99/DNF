#include "stdafx.h"
#include "MeteorState.h"

#include "GameObject.h"
#include "StateMachineComponent.h"
#include "PositionComponent.h"
#include "AnimatorComponent.h"
#include "Animation.h"
#include "AttackCollisionComponent.h"

MeteorIdle::MeteorIdle(StateMachineComponent* stateMachine, GameObject* owner)
	:State(stateMachine, owner)
{
	_animComp = owner->GetComponent<AnimatorComponent>();
}

void MeteorIdle::Update()
{
	if (_animComp->GetCurAnim()->IsEnd())
	{
		ChangeState(eState::NormalAttack1);
	}
}

MeteorAttack::MeteorAttack(StateMachineComponent* stateMachine, GameObject* owner)
	:State(stateMachine, owner)
{
	_posComp = owner->GetComponent<PositionComponent>();
	_atkComp = owner->GetComponent<AttackCollisionComponent>();
}

void MeteorAttack::Init()
{
	_atkComp->SetAttack({ -100, 475, 100, 525 }, -100, 0, 0.0f);

	_targetPointX = (float)_owner->GetPosition().x;
	_targetPointZ = (float)_posComp->GetZ();

	_startPointX = _targetPointX + DISTANCE;
	_startPointZ = _targetPointZ + DISTANCE;

	SetPos((int)_startPointX, _startPointZ);

	_elapsedTime = 0.0f;
}

void MeteorAttack::Update()
{
	_elapsedTime += Timer::GetDeltaTime();

	if (_elapsedTime >= TARGET_TIME)
	{
		SetPos((int)_targetPointX, _targetPointZ);

		ChangeState(eState::Skill1);
		return;
	}

	float curX = (_startPointX + (_targetPointX - _startPointX) * (_elapsedTime / TARGET_TIME));
	float curZ = (_startPointZ + (_targetPointZ - _startPointZ) * (_elapsedTime / TARGET_TIME));

	SetPos((int)curX, curZ);
}

void MeteorAttack::Release()
{
	_atkComp->Init();
}

void MeteorAttack::SetPos(const int& curX, const float& curZ)
{
	_owner->SetX(curX);
	_posComp->SetZ(curZ);
}

MeteorSkill::MeteorSkill(StateMachineComponent* stateMachine, GameObject* owner)
	:State(stateMachine, owner)
{
	_animComp = owner->GetComponent<AnimatorComponent>();
	_atkComp = owner->GetComponent<AttackCollisionComponent>();
}

void MeteorSkill::Update()
{
	int curFrame = _animComp->GetCurAnim()->GetCurFrame();

	if (curFrame == 0)
	{
		_atkComp->SetAttack({ -100, 475, 100, 525 }, 100, 0, 0.0f);
	}
	else if (curFrame == 2)
	{
		_atkComp->SetAttack({ -100, 475, 100, 525 }, 100, 0, 15.0f, 10.0f);
		_atkComp->ClearHitObjs();
	}
	else if (curFrame == 5)
	{
		_atkComp->Init();
	}

	if (_animComp->GetCurAnim()->IsEnd())
	{
		_owner->SetIsActive(false);
		ChangeState(eState::Idle);
	}
}
