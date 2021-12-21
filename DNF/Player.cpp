#include "stdafx.h"
#include "Player.h"

#include "AnimatorComponent.h"
#include "SpriteComponent.h"
#include "RendererComponent.h"

#include "RectComponent.h"
#include "HitBoxComponent.h"

#include "PlayerMovementComponent.h"
#include "PlayerAttackComponent.h"
#include "PlayerStatusUIComponent.h"



#include "Animation.h"
#include "newAnimatorComponent.h"
#include "newSpriteComponent.h"

bool IdleCanChange()
{
	if (false == (Input::GetButton(VK_LEFT) || Input::GetButtonDown(VK_LEFT)) &&
		false == (Input::GetButton(VK_RIGHT) || Input::GetButtonDown(VK_RIGHT)) &&
		false == (Input::GetButton(VK_UP) || Input::GetButtonDown(VK_UP)) &&
		false == (Input::GetButton(VK_DOWN) || Input::GetButtonDown(VK_DOWN)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool WalkCanChange()
{

}

void Player::Init()
{
	AnimatorComponent* animatorComp = new AnimatorComponent(this, 101);
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Idle.png", this), L"Idle");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Walk.png", this), L"Walk");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Run.png", this), L"Run");

	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Jump.png", this), L"Jump");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/JumpDownIdle.png", this), L"JumpDownIdle");

	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/Damaged.png", this), L"Damaged");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/JumpDownDamaged.png", this), L"JumpDownDamaged");

	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/NormalAttack1.png", this), L"NormalAttack1");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/NormalAttack2.png", this), L"NormalAttack2");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/NormalAttack3.png", this), L"NormalAttack3");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/NormalAttack4.png", this), L"NormalAttack4");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/NormalAttack5.png", this), L"NormalAttack5");

	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/NormalAttack2.png", this), L"DashAttack1");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/DashAttack2.png", this), L"DashAttack2");

	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/JumpAttack.png", this), L"JumpAttack");

	//Skill
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Player/SnakeDance.png", this), L"SnakeDance");

	RendererComponent* rendererComp = new RendererComponent(animatorComp, this, 102);
	PlayerMovementComponent* movementComp = new PlayerMovementComponent(this, 91);
	PlayerAttackComponent* attackComp = new PlayerAttackComponent(this, 90);
	PlayerStatusUIComponent* statusComp = new PlayerStatusUIComponent(this, 103);

	RectComponent* bodyCollisionRectComp = new RectComponent(this, 94);
	bodyCollisionRectComp->SetRectSize({ -26,-30,26,10 });
	HitboxComponent* bodyHitboxComp = new HitboxComponent(bodyCollisionRectComp, HitboxComponent::eHitBoxType::Body, this, 95);

	RectComponent* attackCollisionRectComp = new RectComponent(this, 92);
	attackCollisionRectComp->SetRectSize({ 0,0,0,0 });
	mpAttackHitBoxComp = new HitboxComponent(attackCollisionRectComp, HitboxComponent::eHitBoxType::Attack, this, 93);

	Animation* test = new Animation(L"Image/CharacterMotion/Player/Idle.png", 0, IdleCanChange);
	Animation* test = new Animation(L"Image/CharacterMotion/Player/walk.png", 1, IdleCanChange);

	newAnimatorComponent* newAniComp = new newAnimatorComponent(this);
	newSpriteComponent* newSpriteComp = new newSpriteComponent(newAniComp, this);


	Character::Init();
}

void Player::InitAttackHitbox()
{
	mpAttackHitBoxComp->SetAttack(0.0f, 0.0f, { 0,0,0,0 });
}

void Player::SetAttackType(eAttackType atkType) noexcept
{
	mAttackType = atkType;
}

void Player::SetAttackHitbox(float strikingPower, float floatingPower, RECT rect) noexcept
{
	mpAttackHitBoxComp->SetAttack(strikingPower, floatingPower, rect);
}

void Player::AddHP(float value) noexcept
{
	mHP += value;
}

void Player::AddMP(float value) noexcept
{
	mMP += value;
}

Player::eAttackType Player::GetAttackType() const noexcept
{
	return mAttackType;
}

float Player::GetHP() const noexcept
{
	return mHP;
}

float Player::GetMP() const noexcept
{
	return mMP;
}

void Player::OnBodyCollided(RECT intersectionRect)
{
	int width = intersectionRect.right - intersectionRect.left;
	int height = intersectionRect.bottom - intersectionRect.top;

	if (width > height)
	{
		if (intersectionRect.top == mpBodyHitBoxComp->GetRect().top) { AddY(height); }
		else { AddY(-height); }
	}
	else
	{
		if (intersectionRect.left == mpBodyHitBoxComp->GetRect().left) { AddX(width); }
		else { AddX(-width); }
	}
}

void Player::OnAttackCollided(float strikingPower, float floatingPower)
{
	GetComponent<AnimatorComponent>()->Play(L"Damaged");
	AddHP(-strikingPower);
	SetState(eState::Damaged);

	SetAcceleration(floatingPower);
	GetComponent<PlayerMovementComponent>()->SetFlightTime(0.0f);

	// 이미 공중인데 띄우는 힘이 없는 공격에 맞았다면
	if (GetZ() > 0.0f && floatingPower == 0.0f)
	{
		SetAcceleration(5.0f);
	}
}
