#include "stdafx.h"
#include "Goblin.h"

#include "AnimatorComponent.h"
#include "Animation.h"
#include "SpriteComponent.h"

#include "PositionComponent.h"
#include "GoblinStatusComponent.h"
#include "RectColliderComponent.h"
#include "BodyCollisionComponent.h"
#include "TransformComponent.h"

void Goblin::Init()
{
	SetPosition({ 1000,500 });

	GoblinStatusComponent* statusComp = new GoblinStatusComponent(this, 0);

	AnimatorComponent* animComp = new AnimatorComponent(this);

#pragma region AddAnimation

	animComp->AddAnimation(L"Image/CharacterMotion/Goblin/Idle.png", L"Idle");
	animComp->AddAnimation(L"Image/CharacterMotion/Goblin/Damaged.png", L"Damaged");
	animComp->AddAnimation(L"Image/CharacterMotion/Goblin/JumpDamaged1.png", L"JumpDamaged1");
	animComp->AddAnimation(L"Image/CharacterMotion/Goblin/JumpDamaged2.png", L"JumpDamaged2");
	animComp->AddAnimation(L"Image/CharacterMotion/Goblin/JumpDamaged3.png", L"JumpDamaged3");
	animComp->AddAnimation(L"Image/CharacterMotion/Goblin/JumpDownIdle.png", L"JumpDownIdle");

#pragma endregion

#pragma region AddTransition

	using state = GoblinStatusComponent::eGoblinState;

	auto CanChange = [](GameObject* owner, const int& nextStateNum) {
		if ((int)(owner->GetComponent<GoblinStatusComponent>()->GetState()) == nextStateNum)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	animComp->AddTransition(L"Idle", L"Damaged", (int)state::Damaged, CanChange);
	animComp->AddTransition(L"Idle", L"JumpDamaged1", CanChange, (int)state::JumpDamaged);

	animComp->AddTransition(L"JumpDamaged1", L"JumpDamaged2", [](GameObject* owner, int a) {	if ((owner->GetComponent<PositionComponent>()->GetZ()) >= a)
	{
		return true;
	}
	else
	{
		return false;
	}}, 50);
	animComp->AddTransition(L"JumpDamaged2", L"JumpDamaged3", [](GameObject* owner, int a) {	if ((owner->GetComponent<PositionComponent>()->GetZ()) <= a)
	{
		return true;
	}
	else
	{
		return false;
	}}, 50);

	animComp->AddTransition(L"JumpDownIdle", L"JumpDamaged1", CanChange, (int)state::JumpDamaged);
	animComp->AddTransition(L"JumpDownIdle", L"Damaged", CanChange, (int)state::Damaged);

	animComp->AddTransition(L"JumpDamaged1", L"JumpDownIdle", (int)state::JumpDownIdle, CanChange);
	animComp->AddTransition(L"JumpDamaged2", L"JumpDownIdle", (int)state::JumpDownIdle, CanChange);
	animComp->AddTransition(L"JumpDamaged3", L"JumpDownIdle", (int)state::JumpDownIdle, CanChange);

#pragma endregion

	animComp->SetCurrAnim(L"Idle");
	SpriteComponent* spriteComp = new SpriteComponent(this, 101);

	PositionComponent* posComp = new PositionComponent(this, -1);

	TransformComponent* transComp = new TransformComponent(this,99);
	BodyCollisionComponent* bodyColliderComp = new BodyCollisionComponent(new RectColliderComponent({ -20,-25,20,5 }, this, 100), -76, 0, this, 100);

	GameObject::Init();
}
