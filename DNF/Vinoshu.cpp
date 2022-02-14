#include "stdafx.h"
#include "Vinoshu.h"

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
#include "MonsterState.h"
#include "Meteor.h"

void Vinoshu::Init()
{
	SetPosition({ 600,600 });
	
	Meteor* meteor = new Meteor(this->GetScene(), L"Monster");
	meteor->Init();

	StateMachineComponent* stateMachineComp = new StateMachineComponent(this, 0);

	AnimatorComponent* animComp = new AnimatorComponent(this, 102);

	animComp->AddAnimation(L"Image/CharacterMotion/Vinoshu/Idle.png", L"Idle");
	animComp->AddAnimation(L"Image/CharacterMotion/Vinoshu/Casting.png", L"Casting");
	animComp->AddAnimation(L"Image/CharacterMotion/Vinoshu/ForwardWalk.png", L"ForwardWalk");
	animComp->AddAnimation(L"Image/CharacterMotion/Vinoshu/BackwardWalk.png", L"BackwardWalk");
	animComp->AddAnimation(L"Image/CharacterMotion/Vinoshu/NormalAttack.png", L"NormalAttack");

	animComp->AddAnimation(L"Image/CharacterMotion/Vinoshu/Damaged.png", L"Damaged");
	animComp->AddAnimation(L"Image/CharacterMotion/Vinoshu/Down.png", L"Down");
	animComp->AddAnimation(L"Image/CharacterMotion/Vinoshu/DownIdle.png", L"DownIdle");
	animComp->AddAnimation(L"Image/CharacterMotion/Vinoshu/JumpDamagedBounce.png", L"JumpDamagedBounce");
	animComp->AddAnimation(L"Image/CharacterMotion/Vinoshu/LowJumpDamaged.png", L"LowJumpDamaged");
	animComp->AddAnimation(L"Image/CharacterMotion/Vinoshu/HighJumpDamaged.png", L"HighJumpDamaged");


	animComp->SetCurAnimation(L"Idle");

	PositionComponent* posComp = new PositionComponent(this, 99);
	TransformComponent* transformComp = new TransformComponent(this, 101);

	BodyCollisionComponent* bodyColliderComp = new BodyCollisionComponent(new RectColliderComponent({ -20,-25,20,5 }, this, 100), 116, 0, this, 100);
	AttackCollisionComponent* atkColliderComp = new AttackCollisionComponent(new RectColliderComponent({ 0,0,0,0 }, this, 100), this, 100);

	stateMachineComp->AddState(new Idle(stateMachineComp, this), eState::Idle);
	stateMachineComp->AddState(new Walk(stateMachineComp, this), eState::Walk);
	stateMachineComp->AddState(new NormalAttack(stateMachineComp, this), eState::NormalAttack1);
	stateMachineComp->AddState(new AttackReady(stateMachineComp, this), eState::AttackReady);
	stateMachineComp->AddState(new Damaged(stateMachineComp, this), eState::Damaged);

	SpriteComponent* spriteComp = new SpriteComponent(this, 103);

	auto CanChange = [stateMachineComp](const int& nextStateNum) {if (stateMachineComp->GetCurStateTag() == (eState)nextStateNum)
	{
		return true;
	}
	else
	{
		return false;
	}
	};

	animComp->AddTransition(L"Idle", L"ForwardWalk", (int)eState::Walk, CanChange);
	animComp->AddTransition(L"Idle", L"BackwardWalk", (int)eState::Walk, CanChange);

	animComp->AddTransition(L"BackwardWalk", L"ForwardWalk", [stateMachineComp,this, transformComp](const int& none) {
		int targetPosX = ((Walk*)(stateMachineComp->GetCurState()))->GetTarget()->GetX();
		if ((targetPosX > this->GetX()) && (transformComp->GetDirX() == eDirX::Right)
			|| (targetPosX < this->GetX()) && (transformComp->GetDirX() == eDirX::Left))
		{
			return true;
		}
		else
		{
			return false;
		}
		}, 0);
	animComp->AddTransition(L"ForwardWalk", L"BackwardWalk", [stateMachineComp, this, transformComp](const int& none) {
		int targetPosX = ((Walk*)(stateMachineComp->GetCurState()))->GetTarget()->GetX();
		if ((targetPosX > this->GetX()) && (transformComp->GetDirX() == eDirX::Left)
			|| (targetPosX < this->GetX()) && (transformComp->GetDirX() == eDirX::Right))
		{
			return true;
		}
		else
		{
			return false;
		}
		}, 0);

	animComp->AddTransition(L"Idle", L"NormalAttack", (int)eState::NormalAttack1, CanChange);
	animComp->AddTransition(L"ForwardWalk", L"NormalAttack", (int)eState::NormalAttack1, CanChange);
	animComp->AddTransition(L"BackwardWalk", L"NormalAttack", (int)eState::NormalAttack1, CanChange);

	animComp->AddTransition(L"BackwardWalk", L"Casting", (int)eState::AttackReady, CanChange);
	animComp->AddTransition(L"ForwardWalk", L"Casting", (int)eState::AttackReady, CanChange);

	animComp->AddTransition(L"Damaged", CanChange, (int)eState::Damaged);
	animComp->AddTransition(L"Damaged", L"Idle", CanChange, (int)eState::Idle);

	animComp->AddTransition(L"Damaged", L"LowJumpDamaged", [posComp](const int& height)
		{
			if (posComp->GetZ() > height)
			{
				return true;
			}
			else
			{
				return false;
			}
		}, 0);
	animComp->AddTransition(L"Damaged", L"HighJumpDamaged", [posComp](const int& height)
		{
			if (posComp->GetZ() > height)
			{
				return true;
			}
			else
			{
				return false;
			}
		}, 50);
	animComp->AddTransition(L"LowJumpDamaged", L"HighJumpDamaged", [posComp](const int& height)
		{
			if (posComp->GetZ() > height)
			{
				return true;
			}
			else
			{
				return false;
			}
		}, 50);
	animComp->AddTransition(L"LowJumpDamaged", L"JumpDamagedBounce", [stateMachineComp]( const int& none)
		{
			return((Damaged*)(stateMachineComp->GetCurState()))->GetOnGroundOnce();
		}, 0);
	animComp->AddTransition(L"HighJumpDamaged", L"JumpDamagedBounce", [stateMachineComp](const int& none)
		{
			return((Damaged*)(stateMachineComp->GetCurState()))->GetOnGroundOnce();
		}, 0);
	animComp->AddTransition(L"HighJumpDamaged", L"JumpDamagedBounce", [stateMachineComp](const int& none)
		{
			return((Damaged*)(stateMachineComp->GetCurState()))->GetOnGroundOnce();
		}, 0);
	animComp->AddTransition(L"Down", L"DownIdle", [stateMachineComp](const int& elapsedTime)
		{
			return((Damaged*)(stateMachineComp->GetCurState()))->GetGroundElapsedTime() >= elapsedTime/10.0f;
		}, 5);
	animComp->AddTransition(L"JumpDamagedBounce", L"Down", [posComp](const int& height)
		{
			if (posComp->GetZ() <= height)
			{
				return true;
			}
			else
			{
				return false;
			}
		}, 0);
	animComp->AddTransition(L"Down", L"HighJumpDamaged", [posComp](const int& height)
		{
			if (posComp->GetZ() > height)
			{
				return true;
			}
			else
			{
				return false;
			}
		}, 0);

	animComp->AddTransition(L"DownIdle", L"Idle", CanChange, (int)eState::Idle);



	stateMachineComp->ChangeState(eState::Idle);

	GameObject::Init();
}
