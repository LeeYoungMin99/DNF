#include "stdafx.h"
#include "CreateCharacterButton.h"

#include "SceneManager.h"

#include "SpriteComponent.h"
#include "AnimatorComponent.h"
#include "RendererComponent.h"
#include "ButtonComponent.h"
#include "RectComponent.h"
#include "TextComponent.h"

void CreateCharacterButton::Init()
{
	AnimatorComponent* animatorComp = new AnimatorComponent(this, 99);
	animatorComp->AddSprite(new SpriteComponent(L"Image/Button/SmallButtonIdle.png", this), L"Idle");
	animatorComp->AddSprite(new SpriteComponent(L"Image/Button/SmallButtonHover.png", this), L"Hover");
	animatorComp->AddSprite(new SpriteComponent(L"Image/Button/SmallButtonClick.png", this), L"Click");
	RendererComponent* rendererComp = new RendererComponent(animatorComp, this, 100);

	mpAnimatorComp = animatorComp;

	GameObject::Init();
	RectComponent* collisionRect = new RectComponent(this);
	SetPosition({ 318 ,559 });
	collisionRect->SetRectSize({ 0,0,56,24 });

	TextComponent* textComp = new TextComponent(L"캐릭터생성", L"모리스9", 11.0f, D2D1::ColorF(185.0f / 255.0f, 148.0f / 255.0f, 96.0f / 255.0f), this, 101);
	textComp->SetRect({ GetX(),GetY(),GetX() + 56,GetY() + 24 });

	ButtonComponent::ButtonFunction btnFunction(
		&CreateCharacterButton::SetIdle,
		&CreateCharacterButton::SetHover,
		&CreateCharacterButton::SetClick,
		&CreateCharacterButton::SetExecute);

	ButtonComponent* btnComp = new ButtonComponent(collisionRect, this, btnFunction, this);
}

void CreateCharacterButton::SetIdle()
{
	mpAnimatorComp->Play(L"Idle");
	mpAnimatorComp->Pause();
}

void CreateCharacterButton::SetHover()
{
	mpAnimatorComp->Play(L"Hover");
	mpAnimatorComp->Pause();
}

void CreateCharacterButton::SetClick()
{
	mpAnimatorComp->Play(L"Click");
	mpAnimatorComp->Pause();
}

void CreateCharacterButton::SetExecute()
{
	cout << "실행" << endl;
}
