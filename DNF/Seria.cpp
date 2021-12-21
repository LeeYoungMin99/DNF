#include "stdafx.h"
#include "Seria.h"

#include "SpriteComponent.h"
#include "AnimatorComponent.h"
#include "RendererComponent.h"
#include "RectComponent.h"
#include "TextComponent.h"
#include "ButtonComponent.h"

void Seria::Init()
{
	AnimatorComponent* animatorComp = new AnimatorComponent(this, 99);
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Seria/Idle.png", this), L"Idle");
	animatorComp->AddSprite(new SpriteComponent(L"Image/CharacterMotion/Seria/Hover.png", this), L"Hover");
	RendererComponent* rendererComp = new RendererComponent(animatorComp, this, 100);

	mpAnimatorComp = animatorComp;

	GameObject::Init();
	RectComponent* collisionRect = new RectComponent(this);
	SetPosition({ 600 ,350 });
	collisionRect->SetRectSize({ -35,-150,36,0 });

	ButtonComponent::ButtonFunction btnFunction(
		&Seria::SetIdle,
		&Seria::SetHover,
		&Seria::SetClick,
		&Seria::SetExecute);

	ButtonComponent* btnComp = new ButtonComponent(collisionRect, this, btnFunction, this);
}

void Seria::SetIdle()
{
	mpAnimatorComp->Play(L"Idle");
}

void Seria::SetHover()
{
	mpAnimatorComp->Play(L"Hover");
}

void Seria::SetClick()
{
}

void Seria::SetExecute()
{
}
