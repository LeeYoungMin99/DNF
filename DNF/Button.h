#pragma once
#include "GameObject.h"

template <typename SceneType>
class Button : public GameObject
{
private:
	using scene_t = SceneType;
	using callback_t = void(SceneType::*)();

public:
	enum class eButtonState { Idle, Hover, Click, None, };
	Button(scene_t* scene, callback_t callback)
		: GameObject()
	{
		static_assert(is_base_of_v<Scene, SceneType>, "Button can be used in a scene");

		_scene = scene;
		_callback = callback;
	}
	virtual ~Button() = default;

	HRESULT Init(eButtonType type, POINT pos, int sizeX, int sizeY)
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

	virtual void Update() override
	{
		switch (state)
		{
		case Button::eButtonState::Idle:
			if (PtInRect(&collisionRect, g_ptMouse))
				state = eButtonState::Hover;
			break;
		case Button::eButtonState::Hover:
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
					(_scene->*_callback)();
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

	virtual void Render(HDC hdc) override
	{
		Graphics g(hdc);

		switch (state)
		{
		case Button::eButtonState::Idle:
			g.DrawImage(buttonIdleImage, renderPos.X, renderPos.Y, sizeX, sizeY);
			break;
		case Button::eButtonState::Hover:
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

	virtual void Release() override
	{

	}

private:
	scene_t* _scene;
	callback_t _callback;

	POINT pos = {};
	int sizeX = 0;
	int sizeY = 0;
	Image* buttonIdleImage = nullptr;
	Image* buttonPutImage = nullptr;
	Image* buttonClickImage = nullptr;
	eButtonState state = eButtonState::None;

	Point renderPos = {};
	RECT collisionRect = {};
	
};