#include "stdafx.h"
#include "Meteor.h"

#include "StateMachineComponent.h"
#include "MeteorState.h"

#include "Animation.h"
#include "AnimatorComponent.h"
#include "SpriteComponent.h"

#include "RectColliderComponent.h"
#include "BodyCollisionComponent.h"
#include "AttackCollisionComponent.h"

#include "TransformComponent.h"

#include "PositionComponent.h"
#include "MonsterState.h"

void Meteor::Init()
{
	StateMachineComponent* stateMachineComp = new StateMachineComponent(this, 0);

	AnimatorComponent* animComp = new AnimatorComponent(this, 102);

	animComp->AddAnimation(L"Image/CharacterMotion/Meteor/MagicCircle.png", L"Idle");
	animComp->AddAnimation(L"Image/CharacterMotion/Meteor/Falling.png", L"Falling");
	animComp->AddAnimation(L"Image/CharacterMotion/Meteor/Explosion.png", L"Explosion");

	animComp->SetCurrAnim(L"Idle");
	SpriteComponent* spriteComp = new SpriteComponent(this, 103);

	auto CanChange = [stateMachineComp](const int& nextStateNum) {if ((stateMachineComp->GetCurStateTag()) == (eState)nextStateNum)
	{
		return true;
	}
	else
	{
		return false;
	}
	};

	animComp->AddTransition(L"Idle", L"Falling", (int)eState::NormalAttack1, CanChange);
	animComp->AddTransition(L"Falling", L"Explosion", (int)eState::Skill1, CanChange);

	PositionComponent* posComp = new PositionComponent(this, 99);

	AttackCollisionComponent* atkColliderComp = new AttackCollisionComponent(new RectColliderComponent({ 0,0,0,0 }, this, 100), this, 100);

	stateMachineComp->AddState(new MeteorIdle(stateMachineComp, this), eState::Idle);
	stateMachineComp->AddState(new MeteorAttack(stateMachineComp, this), eState::NormalAttack1);
	stateMachineComp->AddState(new MeteorSkill(stateMachineComp, this), eState::Skill1);

	stateMachineComp->ChangeState(eState::Idle);

	SetIsActive(false);

	GameObject::Init();
}
