#include "stdafx.h"
#include "GameShutDownButton.h"

#include "SpriteComponent.h"
#include "Image.h"

void GameShutDownButton::Init()
{
	Button::Init();

	SpriteComponent* buttonImage = new SpriteComponent(L"Image/Button/SmallButton.png", this);
}

void GameShutDownButton::Update()
{
	Button::Update();

	if (mState == Button::eButtonState::Idle)
	{
	}
	else if (mState == Button::eButtonState::Hover)
	{
		if (Input::GetButtonUp(VK_LBUTTON))
		{
			PostQuitMessage(0);
		}
	}
	else if (mState == Button::eButtonState::Click)
	{
	}
}
