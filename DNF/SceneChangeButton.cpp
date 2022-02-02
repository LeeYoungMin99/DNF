#include "stdafx.h"
#include "SceneChangeButton.h"

#include "RectColliderComponent.h"
#include "ButtonComponent.h"
#include "TextComponent.h"
#include "AnimatorComponent.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"

#include "SceneManager.h"

SceneChangeButton::SceneChangeButton(Scene* scene, const wstring& tag, wstring sceneTag)
	:GameObject(scene, tag), _sceneTag{ sceneTag } { }

SceneChangeButton::SceneChangeButton(GameObject* parent, const wstring& tag, wstring sceneTag)
	: GameObject(parent, tag), _sceneTag{ sceneTag } { }

void SceneChangeButton::Init()
{
	RectColliderComponent* collisionRect = new RectColliderComponent({ 0, 0, 100,21 }, this);

	TextComponent* textComp = new TextComponent(L"던전 입장", L"모리스9", 18, { 190,170,150 }, this, 102);
	textComp->SetRect({ 0, 0, 100,21 });

	AnimatorComponent* animComp = new AnimatorComponent(this);

	SpriteComponent* spriteComp = new SpriteComponent(this, 101);

	ButtonComponent* btnComp = new ButtonComponent(collisionRect, this, this);
	PositionComponent* posComp = new PositionComponent(this, 99);

	animComp->AddAnimation(L"Image/NPC_ClickButtonIdle.png", L"Idle");
	animComp->AddAnimation(L"Image/NPC_ClickButtonHover.png", L"Hover");

	auto CanChange = [btnComp](const int& nextStateNum) {
		if ((int)(btnComp->GetState()) == nextStateNum)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	animComp->AddTransition(L"Idle", L"Hover", (int)ButtonComponent::eButtonState::Hover, CanChange);

	animComp->SetCurrAnim(L"Idle");

	GameObject::Init();
}

void SceneChangeButton::OnExecuteToClick()
{
	SceneManager::GetSingleton()->SetNextScene(_sceneTag);

	SetIsActive(false);
}
