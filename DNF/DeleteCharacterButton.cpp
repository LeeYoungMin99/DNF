#include "stdafx.h"
#include "DeleteCharacterButton.h"

#include "SpriteComponent.h"
#include "AnimatorComponent.h"
#include "RendererComponent.h"
#include "TextComponent.h"
#include "Image.h"

void DeleteCharacterButton::Init()
{
	AnimatorComponent* animatorComp = new AnimatorComponent(this);
	animatorComp->AddSprite(new SpriteComponent(L"Image/Button/SmallButton.png", this), L"Idle");
	RendererComponent* rendererComp = new RendererComponent(animatorComp, this);
	TextComponent* textComp = new TextComponent(L"캐릭터삭제", L"모리스9", 11.0f, D2D1::ColorF(185.0f / 255.0f, 148.0f / 255.0f, 96.0f / 255.0f), this, 101);
	Button::Init();
}

void DeleteCharacterButton::Update()
{
	Button::Update();

	if (mState == Button::eButtonState::Idle)
	{
		GetComponent<SpriteComponent>()->SetCurrFrame(0);
	}
	else if (mState == Button::eButtonState::Hover)
	{
		GetComponent<SpriteComponent>()->SetCurrFrame(1);
		if (Input::GetButtonUp(VK_LBUTTON))
		{
			cout << "캐릭터 삭제하는 내용" << endl;
		}
	}
	else if (mState == Button::eButtonState::Click)
	{
		GetComponent<SpriteComponent>()->SetCurrFrame(2);
	}
}
