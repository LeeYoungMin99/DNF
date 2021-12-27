#include "stdafx.h"
#include "Seria.h"

#include "SpriteComponent.h"
#include "AnimatorComponent.h"
#include "Transition.h"

#include "PositionComponent.h"
#include "RectColliderComponent.h"
#include "TextComponent.h"
#include "ButtonComponent.h"

#include "SceneManager.h"

void Seria::Init()
{
	SetPosition({ 600 ,350 });
	RectColliderComponent* collisionRect = new RectColliderComponent({ -35,-150,36,0 }, this);

	AnimatorComponent* animComp = new AnimatorComponent(this);

	auto CanChange = [](GameObject* owner, const int& nextStateNum) {
		if ((int)(owner->GetComponent<ButtonComponent>()->GetState()) == nextStateNum)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	animComp->AddAnimation(L"Image/CharacterMotion/Seria/Idle.png", L"Idle");
	animComp->AddAnimation(L"Image/CharacterMotion/Seria/Hover.png", L"Hover");

	animComp->AddTransition(L"Idle", L"Hover", (int)ButtonComponent::eButtonState::Hover, CanChange);

	animComp->SetCurrAnim(L"Idle");
	SpriteComponent* spriteComp = new SpriteComponent(this, 101);

	ButtonComponent* btnComp = new ButtonComponent(collisionRect, this, this);
	PositionComponent* posComp = new PositionComponent(this, 99);

	GameObject::Init();
}

void Seria::OnExecute()
{
	SceneManager::GetSingleton()->SetNextScene(L"Battle");
}

