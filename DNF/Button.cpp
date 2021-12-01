#include "stdafx.h"
#include "Button.h"

Button::Button(CharacterSelectScene* _scene, Callback bf)
	:scene{_scene}, buttonFunction{bf} { }

HRESULT Button::Init(eButtonType type, POINT pos, int sizeX, int sizeY)
{
	this->pos = pos;

	switch (type)
	{
	case eButtonType::Small:
		this->buttonIdleImage = FROM_FILE(L"Image/Button/SmallButtonIdleImage.png");
		this->buttonPutImage = FROM_FILE(L"Image/Button/SmallButtonPutImage.png");
		this->buttonClickImage = FROM_FILE(L"Image/Button/SmallButtonClickImage.png");
		break;
	case eButtonType::Middle:
		this->buttonIdleImage = FROM_FILE(L"Image/Button/MiddleButtonIdleImage.png");
		this->buttonPutImage = FROM_FILE(L"Image/Button/MiddleButtonPutImage.png");
		this->buttonClickImage = FROM_FILE(L"Image/Button/MiddleButtonClickImage.png");
		break;
	case eButtonType::Large:
		this->buttonIdleImage = FROM_FILE(L"Image/Button/LargeButtonIdleImage.png");
		this->buttonPutImage = FROM_FILE(L"Image/Button/LargeButtonPutImage.png");
		this->buttonClickImage = FROM_FILE(L"Image/Button/LargeButtonClickImage.png");
		break;
	case eButtonType::Long:
		this->buttonIdleImage = FROM_FILE(L"Image/Button/LongButtonIdleImage.png");
		this->buttonPutImage = FROM_FILE(L"Image/Button/LongButtonPutImage.png");
		this->buttonClickImage = FROM_FILE(L"Image/Button/LongButtonClickImage.png");
		break;
	case eButtonType::None:
	default:
		break;
	}

	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->state = eButtonState::Idle;

	renderPos = { pos.x - (sizeX / 2), pos.y - (sizeY / 2) };
	collisionRect = { renderPos.X, renderPos.Y, pos.x + (sizeX / 2), pos.y + (sizeY / 2) };

	return S_OK;
}

void Button::Update()
{
	switch (state)
	{
	case Button::eButtonState::Idle:
		if (PtInRect(&collisionRect, g_ptMouse))
			state = eButtonState::Put;
		break;
	case Button::eButtonState::Put:
		if (MGR_KEY->IsOnceKeyDown(VK_LBUTTON))
			state = eButtonState::Click;
		else if (false == PtInRect(&collisionRect, g_ptMouse))
			state = eButtonState::Idle;
		break;
	case Button::eButtonState::Click:
		if (MGR_KEY->IsOnceKeyUp(VK_LBUTTON))
		{
			if (PtInRect(&collisionRect, g_ptMouse))
			{
				(*scene.*buttonFunction)();
			}
			state = eButtonState::Idle;
		}
		break;
	case Button::eButtonState::None:
		break;
	default:
		break;
	}
}

void Button::Render(HDC hdc)
{
	Graphics g(hdc);

	switch (state)
	{
	case Button::eButtonState::Idle:
		g.DrawImage(buttonIdleImage, renderPos.X, renderPos.Y, sizeX, sizeY);
		break;
	case Button::eButtonState::Put:
		g.DrawImage(buttonPutImage, renderPos.X, renderPos.Y, sizeX, sizeY);
		break;
	case Button::eButtonState::Click:
		g.DrawImage(buttonClickImage, renderPos.X, renderPos.Y, sizeX, sizeY);
		break;
	case Button::eButtonState::None:
	default:
		break;
	}
}

void Button::Release()
{
}
