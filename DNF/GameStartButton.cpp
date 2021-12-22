#include "stdafx.h"
#include "GameStartButton.h"

#include "SceneManager.h"

#include "SpriteComponent.h"
#include "AnimatorComponent.h"
#include "RendererComponent.h"
#include "ButtonComponent.h"
#include "RectComponent.h"

void GameStartButton::Init()
{
	AnimatorComponent* animatorComp = new AnimatorComponent(this, 99);
	animatorComp->AddSprite(new SpriteComponent(L"Image/Button/StartButtonIdle.png", this), L"Idle");
	animatorComp->AddSprite(new SpriteComponent(L"Image/Button/StartButtonHover.png", this), L"Hover");
	animatorComp->AddSprite(new SpriteComponent(L"Image/Button/StartButtonClick.png", this), L"Click");
	RendererComponent* rendererComp = new RendererComponent(animatorComp, this, 100);

	mpAnimatorComp = animatorComp;

	GameObject::Init();
	RectComponent* collisionRect = new RectComponent(this);
	SetPosition({ 450,548 });
	collisionRect->SetRectSize({ 0, 0, 170, 47 });

	ButtonComponent* btnComp = new ButtonComponent(collisionRect, this, this);
}

void GameStartButton::OnIdle()
{
	mpAnimatorComp->Play(L"Idle");
	mpAnimatorComp->Pause();
}

void GameStartButton::OnHover()
{
	mpAnimatorComp->Play(L"Hover");
	mpAnimatorComp->Pause();
}

void GameStartButton::OnClick()
{
	mpAnimatorComp->Play(L"Click");
	mpAnimatorComp->Pause();
}

void GameStartButton::OnExecute()
{
	SceneManager::GetSingleton()->SetNextScene(L"Town");
}
