#include "stdafx.h"
#include "CreateCharacterButton.h"

#include "SceneManager.h"
#include "SpriteComponent.h"
#include "Image.h"

void CreateCharacterButton::Init()
{
	Button::Init();

	SpriteComponent* buttonImage = new SpriteComponent(L"Image/Button/SmallButton.png", this);
}

void CreateCharacterButton::Update()
{
	Button::Update();
	if (mState == Button::eButtonState::Idle)
	{
	}
	else if (mState == Button::eButtonState::Hover)
	{
		if (Input::GetButtonUp(VK_LBUTTON))
		{
			SceneManager::GetSingleton()->SetNextScene(L"CreateCharacter");
		}
	}
	else if (mState == Button::eButtonState::Click)
	{
	}
}
