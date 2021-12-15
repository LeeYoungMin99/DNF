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
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Idle.png", this), L"Idle");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Walk.png", this), L"Walk");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Run.png", this), L"Run");

	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/NormalAttack1.png", this), L"NormalAttack1");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/NormalAttack2.png", this), L"NormalAttack2");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/NormalAttack3.png", this), L"NormalAttack3");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/NormalAttack4.png", this), L"NormalAttack4");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/NormalAttack5.png", this), L"NormalAttack5");

	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/NormalAttack2.png", this), L"DashAttack1");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/DashAttack2.png", this), L"DashAttack2");

	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Jump.png", this), L"Jump");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/JumpDownIdle.png", this), L"JumpDownIdle");

	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/JumpAttack.png", this), L"JumpAttack");

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
