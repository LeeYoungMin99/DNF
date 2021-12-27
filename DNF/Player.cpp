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
#include "PlayerStatusComponent.h"
#include "PlayerCommandComponent.h"

void Player::Init()
{
	SetPosition({ 500,450 });

	PlayerStatusComponent* statusComp = new PlayerStatusComponent(this, 0);

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

	using state = PlayerStatusComponent::ePlayerState;

	auto CanChange = [](GameObject* owner, const int& nextStateNum) {if ((int)(owner->GetComponent<PlayerStatusComponent>()->GetState()) == nextStateNum)
	{
		return true;
	}
	else
	{
		return false;
	}
	};

	animComp->AddTransition(L"Idle", L"Walk", (int)state::Walk, CanChange);
	animComp->AddTransition(L"Idle", L"Run", (int)state::Run, CanChange);
	animComp->AddTransition(L"Walk", L"Run", (int)state::Run, CanChange);
	animComp->AddTransition(L"Run", L"Walk", (int)state::Walk, CanChange);

	animComp->AddTransition(L"Idle", L"Jump1", CanChange, (int)state::Jump);
	animComp->AddTransition(L"Walk", L"Jump1", CanChange, (int)state::Jump);
	animComp->AddTransition(L"Run", L"Jump1", CanChange, (int)state::Jump);
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
	animComp->AddTransition(L"Jump3", L"JumpDownIdle", (int)state::JumpDownIdle, CanChange);

	animComp->AddTransition(L"Jump1", L"JumpAttack", CanChange, (int)state::JumpAttack);
	animComp->AddTransition(L"Jump2", L"JumpAttack", CanChange, (int)state::JumpAttack);
	animComp->AddTransition(L"Jump3", L"JumpAttack", CanChange, (int)state::JumpAttack);
	animComp->AddTransition(L"JumpAttack", L"JumpDownIdle", (int)state::JumpDownIdle, CanChange);

	animComp->AddTransition(L"Idle", L"NormalAttack1", (int)state::NormalAttack1, CanChange);
	animComp->AddTransition(L"Walk", L"NormalAttack1", (int)state::NormalAttack1, CanChange);

	animComp->AddTransition(L"NormalAttack1", L"NormalAttack2", (int)state::NormalAttack2, CanChange);
	animComp->AddTransition(L"NormalAttack2", L"NormalAttack3", (int)state::NormalAttack3, CanChange);
	animComp->AddTransition(L"NormalAttack3", L"NormalAttack4", (int)state::NormalAttack4, CanChange);
	animComp->AddTransition(L"NormalAttack4", L"NormalAttack5", (int)state::NormalAttackEnd, CanChange);

	animComp->AddTransition(L"Run", L"DashAttackStart", (int)state::DashAttackStart, CanChange);
	animComp->AddTransition(L"DashAttackStart", L"DashAttackEnd", (int)state::DashAttackEnd, CanChange);

	animComp->AddTransition(L"Idle", L"Upper", (int)state::UpperSlash, CanChange);
	animComp->AddTransition(L"Walk", L"Upper", (int)state::UpperSlash, CanChange);
	animComp->AddTransition(L"Run", L"Upper", (int)state::UpperSlash, CanChange);
	animComp->AddTransition(L"NormalAttack1", L"Upper", (int)state::UpperSlash, CanChange);
	animComp->AddTransition(L"NormalAttack2", L"Upper", (int)state::UpperSlash, CanChange);
	animComp->AddTransition(L"NormalAttack3", L"Upper", (int)state::UpperSlash, CanChange);
	animComp->AddTransition(L"NormalAttack4", L"Upper", (int)state::UpperSlash, CanChange);
	animComp->AddTransition(L"NormalAttack5", L"Upper", (int)state::UpperSlash, CanChange);

	animComp->AddTransition(L"Idle", L"SnakeDance", (int)state::SnakeDance, CanChange);
	animComp->AddTransition(L"Walk", L"SnakeDance", (int)state::SnakeDance, CanChange);
	animComp->AddTransition(L"Run", L"SnakeDance", (int)state::SnakeDance, CanChange);
	animComp->AddTransition(L"NormalAttack1", L"SnakeDance", (int)state::SnakeDance, CanChange);
	animComp->AddTransition(L"NormalAttack2", L"SnakeDance", (int)state::SnakeDance, CanChange);
	animComp->AddTransition(L"NormalAttack3", L"SnakeDance", (int)state::SnakeDance, CanChange);
	animComp->AddTransition(L"NormalAttack4", L"SnakeDance", (int)state::SnakeDance, CanChange);
	animComp->AddTransition(L"NormalAttack5", L"SnakeDance", (int)state::SnakeDance, CanChange);

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

	GameObject::Init();
}
