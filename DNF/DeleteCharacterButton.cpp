#include "stdafx.h"
#include "DeleteCharacterButton.h"

#include "SpriteComponent.h"
#include "Image.h"

void DeleteCharacterButton::Init()
{
	Button::Init();

	SpriteComponent* buttonImage = new SpriteComponent(L"Image/Button/SmallButton.png", this);
}

void DeleteCharacterButton::Update()
{
	Button::Update();

	if (mState == Button::eButtonState::Idle)
	{
	}
	else if (mState == Button::eButtonState::Hover)
	{
		if (Input::GetButtonUp(VK_LBUTTON))
		{
			cout << "ĳ���� �����ϴ� ����" << endl;
		}
	}
	else if (mState == Button::eButtonState::Click)
	{
	}
}
