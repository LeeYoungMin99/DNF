#include "stdafx.h"
#include "GameStartButton.h"

#include "SceneManager.h"
#include "SpriteComponent.h"
#include "AnimatorComponent.h"
#include "RendererComponent.h"
#include "Image.h"

void GameStartButton::Init()
{
	AnimatorComponent* animatorComp = new AnimatorComponent(this);
	animatorComp->AddSprite(new SpriteComponent(L"Image/Button/LargeButton.png", this), L"Idle");
	RendererComponent* rendererComp = new RendererComponent(animatorComp, this);
	Button::Init();
}

void GameStartButton::Update()
{
	Button::Update();
	
	if (mState == Button::eButtonState::Idle)
	{
		GetComponent<SpriteComponent>()->mCurrFrame = 0;
	}
	else if (mState == Button::eButtonState::Hover)
	{
		GetComponent<SpriteComponent>()->mCurrFrame = 1;
		if (Input::GetButtonUp(VK_LBUTTON))
		{
			SceneManager::GetSingleton()->SetNextScene(L"Town");
		}
	}
	else if (mState == Button::eButtonState::Click)
	{
		GetComponent<SpriteComponent>()->mCurrFrame = 2;
	}
}
