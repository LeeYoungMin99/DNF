#include "stdafx.h"
#include "Player.h"

#include "Animation.h"
#include "AnimatorComponent.h"
#include "SpriteComponent.h"

#include "RectColliderComponent.h"
#include "BodyCollisionComponent.h"
#include "AttackCollisionComponent.h"

#include "PositionComponent.h"
#include "PlayerTransformComponent.h"
#include "PlayerMovementComponent.h"
#include "PlayerAttackComponent.h"
#include "PlayerCommandComponent.h"

#include "StateMachineComponent.h"
#include "PlayerState.h"

void Player::Init()
{
	SetPosition({ 600,520 });

	StateMachineComponent* stateMachineComp = new StateMachineComponent(this, 0);

#pragma region AddAnimation

	AnimatorComponent* animComp = new AnimatorComponent(this, 102);

	animComp->AddAnimation(L"Image/CharacterMotion/Player/Idle.png", L"Idle");
	animComp->AddAnimation(L"Image/CharacterMotion/Player/Walk.png", L"Walk");
	animComp->AddAnimation(L"Image/CharacterMotion/Player/Run.png", L"Run");
	animComp->AddAnimation(L"Image/CharacterMotion/Player/Jump1.png", L"Jump1");
	animComp->AddAnimation(L"Image/CharacterMotion/Player/Jump2.png", L"Jump2");
	animComp->AddAnimation(L"Image/CharacterMotion/Player/Jump3.png", L"Jump3");
	animComp->AddAnimation(L"Image/CharacterMotion/Player/JumpDownIdle.png", L"JumpDownIdle");
	animComp->AddAnimation(L"Image/CharacterMotion/Player/JumpAttack.png", L"JumpAttack");

	animComp->AddAnimation(L"Image/CharacterMotion/Player/NormalAttack1.png", L"NormalAttack1");
	animComp->AddAnimation(L"Image/CharacterMotion/Player/NormalAttack2.png", L"NormalAttack2");
	animComp->AddAnimation(L"Image/CharacterMotion/Player/NormalAttack3.png", L"NormalAttack3");
	animComp->AddAnimation(L"Image/CharacterMotion/Player/NormalAttack4.png", L"NormalAttack4");
	animComp->AddAnimation(L"Image/CharacterMotion/Player/NormalAttack5.png", L"NormalAttack5");

	animComp->AddAnimation(L"Image/CharacterMotion/Player/NormalAttack2.png", L"DashAttackStart"); // NormalAttack2 랑 이미지 같음.
	animComp->AddAnimation(L"Image/CharacterMotion/Player/DashAttackEnd.png", L"DashAttackEnd");

	animComp->AddAnimation(L"Image/CharacterMotion/Player/UpperSlash.png", L"Upper");
	animComp->AddAnimation(L"Image/CharacterMotion/Player/SnakeDance.png", L"SnakeDance");

#pragma endregion

#pragma region AddTransition

	using state = eState;

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
	animComp->AddTransition(L"Idle", L"Run", (int)eState::Run, CanChange);
	animComp->AddTransition(L"Walk", L"Run", (int)eState::Run, CanChange);
	animComp->AddTransition(L"Run", L"Walk", (int)eState::Walk, CanChange);

	animComp->AddTransition(L"Idle", L"Jump1", CanChange, (int)eState::Jump);
	animComp->AddTransition(L"Walk", L"Jump1", CanChange, (int)eState::Jump);
	animComp->AddTransition(L"Run", L"Jump1", CanChange, (int)eState::Jump);
	animComp->AddTransition(L"Jump1", L"Jump2", [](GameObject* owner, int height)
		{
			if (owner->GetComponent<PositionComponent>()->GetZ() >= height)
			{
				return true;
			}
			else
			{
				return false;
			}}, 50);
	animComp->AddTransition(L"Jump2", L"Jump3", [](GameObject* owner, int accel)
		{
			if (owner->GetComponent<PositionComponent>()->GetResistance() >= accel)
			{
				return true;
			}
			else
			{
				return false;
			}}, 20);
	animComp->AddTransition(L"Jump3", L"JumpDownIdle", (int)eState::JumpDownIdle, CanChange);

	animComp->AddTransition(L"Jump1", L"JumpAttack", CanChange, (int)eState::JumpAttack);
	animComp->AddTransition(L"Jump2", L"JumpAttack", CanChange, (int)eState::JumpAttack);
	animComp->AddTransition(L"Jump3", L"JumpAttack", CanChange, (int)eState::JumpAttack);
	animComp->AddTransition(L"JumpAttack", L"JumpDownIdle", (int)eState::JumpDownIdle, CanChange);

	animComp->AddTransition(L"Idle", L"NormalAttack1", (int)eState::NormalAttack1, CanChange);
	animComp->AddTransition(L"Walk", L"NormalAttack1", (int)eState::NormalAttack1, CanChange);

	animComp->AddTransition(L"NormalAttack1", L"NormalAttack2", (int)eState::NormalAttack2, CanChange);
	animComp->AddTransition(L"NormalAttack2", L"NormalAttack3", (int)eState::NormalAttack3, CanChange);
	animComp->AddTransition(L"NormalAttack3", L"NormalAttack4", (int)eState::NormalAttack4, CanChange);
	animComp->AddTransition(L"NormalAttack4", L"NormalAttack5", (int)eState::NormalAttack5, CanChange);

	animComp->AddTransition(L"Run", L"DashAttackStart", (int)eState::DashAttack1, CanChange);
	animComp->AddTransition(L"DashAttackStart", L"DashAttackEnd", (int)eState::DashAttack2, CanChange);

	animComp->AddTransition(L"Idle", L"Upper", (int)eState::Skill1, CanChange);
	animComp->AddTransition(L"Walk", L"Upper", (int)eState::Skill1, CanChange);
	animComp->AddTransition(L"Run", L"Upper", (int)eState::Skill1, CanChange);
	animComp->AddTransition(L"NormalAttack1", L"Upper", (int)eState::Skill1, CanChange);
	animComp->AddTransition(L"NormalAttack2", L"Upper", (int)eState::Skill1, CanChange);
	animComp->AddTransition(L"NormalAttack3", L"Upper", (int)eState::Skill1, CanChange);
	animComp->AddTransition(L"NormalAttack4", L"Upper", (int)eState::Skill1, CanChange);
	animComp->AddTransition(L"NormalAttack5", L"Upper", (int)eState::Skill1, CanChange);

	animComp->AddTransition(L"Idle", L"SnakeDance", (int)eState::Skill2, CanChange);
	animComp->AddTransition(L"Walk", L"SnakeDance", (int)eState::Skill2, CanChange);
	animComp->AddTransition(L"Run", L"SnakeDance", (int)eState::Skill2, CanChange);
	animComp->AddTransition(L"NormalAttack1", L"SnakeDance", (int)eState::Skill2, CanChange);
	animComp->AddTransition(L"NormalAttack2", L"SnakeDance", (int)eState::Skill2, CanChange);
	animComp->AddTransition(L"NormalAttack3", L"SnakeDance", (int)eState::Skill2, CanChange);
	animComp->AddTransition(L"NormalAttack4", L"SnakeDance", (int)eState::Skill2, CanChange);
	animComp->AddTransition(L"NormalAttack5", L"SnakeDance", (int)eState::Skill2, CanChange);

#pragma endregion

	animComp->SetCurrAnim(L"Idle");
	SpriteComponent* spriteComp = new SpriteComponent(this, 103);

	PositionComponent* posComp = new PositionComponent(this, 99);
	PlayerTransformComponent* transformComp = new PlayerTransformComponent(this, 101);
	PlayerMovementComponent* movementComp = new PlayerMovementComponent(this, 98);

	PlayerCommandComponent* commandComp = new PlayerCommandComponent(this, 1);

	BodyCollisionComponent* bodyColliderComp = new BodyCollisionComponent(new RectColliderComponent({ -20,-25,20,5 }, this, 100), 0, -116, this, 100);
	AttackCollisionComponent* atkColliderComp = new AttackCollisionComponent(new RectColliderComponent({ 0,0,0,0 }, this, 100), this, 100);
	PlayerAttackComponent* atkComp = new PlayerAttackComponent(this, 99);

#pragma region AddState

	stateMachineComp->AddState(new PlayerIdle(stateMachineComp, this), eState::Idle);
	stateMachineComp->AddState(new PlayerWalk(stateMachineComp, this), eState::Walk);
	stateMachineComp->AddState(new PlayerRun(stateMachineComp, this), eState::Run);
	stateMachineComp->AddState(new PlayerJump(stateMachineComp, this), eState::Jump);
	stateMachineComp->AddState(new PlayerJumpAttack(stateMachineComp, this), eState::JumpAttack);
	stateMachineComp->AddState(new PlayerAction(stateMachineComp, this), eState::JumpDownIdle);
	stateMachineComp->AddState(new PlayerAttack(stateMachineComp, this), eState::DashAttack1);
	stateMachineComp->AddState(new PlayerAttack(stateMachineComp, this), eState::DashAttack2);
	stateMachineComp->AddState(new PlayerAttack(stateMachineComp, this), eState::NormalAttack1);
	stateMachineComp->AddState(new PlayerAttack(stateMachineComp, this), eState::NormalAttack2);
	stateMachineComp->AddState(new PlayerAttack(stateMachineComp, this), eState::NormalAttack3);
	stateMachineComp->AddState(new PlayerAttack(stateMachineComp, this), eState::NormalAttack4);
	stateMachineComp->AddState(new PlayerAttack(stateMachineComp, this), eState::NormalAttack5);
	stateMachineComp->AddState(new PlayerAction(stateMachineComp, this), eState::Skill1);
	stateMachineComp->AddState(new PlayerAction(stateMachineComp, this), eState::Skill2);

	stateMachineComp->ChangeState(eState::Idle);
#pragma endregion


	GameObject::Init();
}
