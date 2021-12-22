#include "stdafx.h"
#include "DeleteCharacterButton.h"

#include "SceneManager.h"

#include "SpriteComponent.h"
#include "AnimatorComponent.h"
#include "RendererComponent.h"
#include "ButtonComponent.h"
#include "RectComponent.h"
#include "TextComponent.h"

void DeleteCharacterButton::Init()
{
	AnimatorComponent* animatorComp = new AnimatorComponent(this, 99);
	animatorComp->AddSprite(new SpriteComponent(L"Image/Button/SmallButtonIdle.png", this), L"Idle");
	animatorComp->AddSprite(new SpriteComponent(L"Image/Button/SmallButtonHover.png", this), L"Hover");
	animatorComp->AddSprite(new SpriteComponent(L"Image/Button/SmallButtonClick.png", this), L"Click");
	RendererComponent* rendererComp = new RendererComponent(animatorComp, this, 100);

	mpAnimatorComp = animatorComp;

	GameObject::Init();
	RectComponent* collisionRect = new RectComponent(this);
	SetPosition({ 384 ,559 });
	collisionRect->SetRectSize({ 0,0,56,24 });

	TextComponent* textComp = new TextComponent(L"ĳ���ͻ���", L"�𸮽�9", 11.0f, D2D1::ColorF(185.0f / 255.0f, 148.0f / 255.0f, 96.0f / 255.0f), this, 101);
	textComp->SetRect({ GetX(),GetY(),GetX() + 56,GetY() + 24 });

	ButtonComponent* btnComp = new ButtonComponent(collisionRect, this, this);
}

void DeleteCharacterButton::OnIdle()
{
	mpAnimatorComp->Play(L"Idle");
	mpAnimatorComp->Pause();
}

void DeleteCharacterButton::OnHover()
{
	mpAnimatorComp->Play(L"Hover");
	mpAnimatorComp->Pause();
}

void DeleteCharacterButton::OnClick()
{
	mpAnimatorComp->Play(L"Click");
	mpAnimatorComp->Pause();
}

void DeleteCharacterButton::OnExecute()
{
	cout << "����" << endl;
}
