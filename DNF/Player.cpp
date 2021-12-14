#include "stdafx.h"
#include "Player.h"

#include "AnimatorComponent.h"
#include "SpriteComponent.h"
#include "RendererComponent.h"
#include "PlayerMovementComponent.h"
#include "PlayerAttackComponent.h"

void Player::Init()
{
	AnimatorComponent* animatorComp = new AnimatorComponent(this, 101);
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Left/Idle.png", this), L"LeftIdle");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Left/Walk.png", this), L"LeftWalk");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Left/Run.png", this), L"LeftRun");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Right/Idle.png", this), L"RightIdle");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Right/Walk.png", this), L"RightWalk");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Right/Run.png", this), L"RightRun");

	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Left/NormalAttack1.png", this), L"LeftNormalAttack1");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Left/NormalAttack2.png", this), L"LeftNormalAttack2");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Left/NormalAttack3.png", this), L"LeftNormalAttack3");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Left/NormalAttack4.png", this), L"LeftNormalAttack4");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Left/NormalAttack5.png", this), L"LeftNormalAttack5");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Right/NormalAttack1.png", this), L"RightNormalAttack1");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Right/NormalAttack2.png", this), L"RightNormalAttack2");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Right/NormalAttack3.png", this), L"RightNormalAttack3");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Right/NormalAttack4.png", this), L"RightNormalAttack4");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Right/NormalAttack5.png", this), L"RightNormalAttack5");

	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Left/NormalAttack2.png", this), L"LeftDashAttack1");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Left/DashAttack2.png", this), L"LeftDashAttack2");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Right/NormalAttack2.png", this), L"RightDashAttack1");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Right/DashAttack2.png", this), L"RightDashAttack2");

	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Left/Jump.png", this), L"LeftJump");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Left/JumpDownIdle.png", this), L"LeftJumpDownIdle");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Right/Jump.png", this), L"RightJump");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Right/JumpDownIdle.png", this), L"RightJumpDownIdle");

	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Left/JumpAttack.png", this), L"LeftJumpAttack");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Right/JumpAttack.png", this), L"RightJumpAttack");

	RendererComponent* rendererComp = new RendererComponent(animatorComp, this, 102);
	PlayerMovementComponent* movementComp = new PlayerMovementComponent(this, 100);
	PlayerAttackComponent* attackComp = new PlayerAttackComponent(this, 99);

	Character::Init();
}

void Player::SetAttackType(eAttackType atkType) noexcept
{
	mAttackType = atkType;
}

Player::eAttackType Player::GetAttackType() const noexcept
{
	return mAttackType;
}
