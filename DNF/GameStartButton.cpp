#include "stdafx.h"
#include "GameStartButton.h"

#include "SceneManager.h"
#include "SpriteComponent.h"
#include "Image.h"

void GameStartButton::Init()
{
	Button::Init();

	SpriteComponent* buttonImage = new SpriteComponent(L"Image/Button/LargeButton.png", this);
}

void GameStartButton::Update()
{
	Button::Update();

	if (mState == Button::eButtonState::Idle)
	{
	}
	else if (mState == Button::eButtonState::Hover)
	{
		if (Input::GetButtonUp(VK_LBUTTON))
		{
			SceneManager::GetSingleton()->SetNextScene(L"Town");
		}
	}
	else if (mState == Button::eButtonState::Click)
	{
	}
}
