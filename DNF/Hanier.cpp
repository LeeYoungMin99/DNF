#include "stdafx.h"
#include "Hanier.h"

#include "StateMachineComponent.h"
#include "MonsterState.h"

#include "Animation.h"
#include "AnimatorComponent.h"
#include "SpriteComponent.h"

#include "RectColliderComponent.h"
#include "BodyCollisionComponent.h"
#include "AttackCollisionComponent.h"

#include "TransformComponent.h"

#include "PositionComponent.h"

void Hanier::Init()
{
	SetPosition({ 600,520 });

	StateMachineComponent* stateMachineComp = new StateMachineComponent(this, 0);

	AnimatorComponent* animComp = new AnimatorComponent(this, 102);

	animComp->AddAnimation(L"Image/CharacterMotion/Hanier/Idle.png", L"Idle");
	animComp->AddAnimation(L"Image/CharacterMotion/Hanier/Walk.png", L"Walk");
	animComp->AddAnimation(L"Image/CharacterMotion/Hanier/NormalAttack1.png", L"NormalAttack1");
	animComp->AddAnimation(L"Image/CharacterMotion/Hanier/NormalAttack2.png", L"NormalAttack2");

	animComp->SetCurrAnim(L"Idle");
	SpriteComponent* spriteComp = new SpriteComponent(this, 103);

	auto CanChange = [](GameObject* owner, const int& nextStateNum) {if ((owner->GetComponent<StateMachineComponent>()->GetCurStateTag()) == nextStateNum)
	{
		return true;
	}
	else
	{
		return false;
	}
	};

	animComp->AddTransition(L"Idle", L"Walk", (int)eState::Walk, CanChange);
	animComp->AddTransition(L"Walk", L"NormalAttack1", CanChange, (int)eState::NormalAttack1);
	animComp->AddTransition(L"NormalAttack1", L"NormalAttack2", [](GameObject* owner, const int& frame) {
		if (owner->GetComponent<AnimatorComponent>()->GetCurAnim()->GetCurrFrame() == frame)
		{
			return true;
		}
		else
		{
			return false;
		}
		}, 6);
	animComp->AddTransition(L"NormalAttack2", L"Idle", CanChange, (int)eState::Idle);

	PositionComponent* posComp = new PositionComponent(this, 99);
	TransformComponent* transformComp = new TransformComponent(this, 101);

	BodyCollisionComponent* bodyColliderComp = new BodyCollisionComponent(new RectColliderComponent({ -20,-25,20,5 }, this, 100), 0, -116, this, 100);
	AttackCollisionComponent* atkColliderComp = new AttackCollisionComponent(new RectColliderComponent({ 0,0,0,0 }, this, 100), this, 100);

	stateMachineComp->AddState(new Idle(stateMachineComp, this), eState::Idle);
	stateMachineComp->AddState(new Walk(stateMachineComp, this), eState::Walk);
	stateMachineComp->AddState(new AttackReady(stateMachineComp, this), eState::AttackReady);
	stateMachineComp->AddState(new NormalAttack(stateMachineComp, this), eState::NormalAttack1);

	stateMachineComp->ChangeState(eState::Idle);

	GameObject::Init();
}
