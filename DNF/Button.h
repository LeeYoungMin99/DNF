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
	enum class eButtonType { Small, Middle, Large, Long, None };
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
		this->mPos = { float(pos.x),float(pos.y) };

		switch (type)
		{
		case eButtonType::Small:
			this->mpButtonIdleImage = FROM_FILE(L"Image/Button/SmallButtonIdleImage.png");
			this->mpButtonPutImage = FROM_FILE(L"Image/Button/SmallButtonPutImage.png");
			this->mpButtonClickImage = FROM_FILE(L"Image/Button/SmallButtonClickImage.png");
			break;
		case eButtonType::Middle:
			this->mpButtonIdleImage = FROM_FILE(L"Image/Button/MiddleButtonIdleImage.png");
			this->mpButtonPutImage = FROM_FILE(L"Image/Button/MiddleButtonPutImage.png");
			this->mpButtonClickImage = FROM_FILE(L"Image/Button/MiddleButtonClickImage.png");
			break;
		case eButtonType::Large:
			this->mpButtonIdleImage = FROM_FILE(L"Image/Button/LargeButtonIdleImage.png");
			this->mpButtonPutImage = FROM_FILE(L"Image/Button/LargeButtonPutImage.png");
			this->mpButtonClickImage = FROM_FILE(L"Image/Button/LargeButtonClickImage.png");
			break;
		case eButtonType::Long:
			this->mpButtonIdleImage = FROM_FILE(L"Image/Button/LongButtonIdleImage.png");
			this->mpButtonPutImage = FROM_FILE(L"Image/Button/LongButtonPutImage.png");
			this->mpButtonClickImage = FROM_FILE(L"Image/Button/LongButtonClickImage.png");
			break;
		case eButtonType::None:
		default:
			break;
		}

		this->mSizeX = sizeX;
		this->mSizeY = sizeY;
		this->mState = eButtonState::Idle;

		mRenderPos = { pos.x - (sizeX / 2), pos.y - (sizeY / 2) };
		mCollisionRect = { mRenderPos.X, mRenderPos.Y, pos.x + (sizeX / 2), pos.y + (sizeY / 2) };

		return S_OK;
	}

	virtual void Update() override
	{
		switch (mState)
		{
		case Button::eButtonState::Idle:
			if (PtInRect(&mCollisionRect, g_ptMouse))
				mState = eButtonState::Hover;
			break;
		case Button::eButtonState::Hover:
			if (false == PtInRect(&mCollisionRect, g_ptMouse))
				mState = eButtonState::Idle;

			if (MGR_KEY->IsStayKeyDown(VK_LBUTTON))
				mState = eButtonState::Click;
			break;
		case Button::eButtonState::Click:
			if (false == PtInRect(&mCollisionRect, g_ptMouse))
				mState = eButtonState::Idle;

			if (MGR_KEY->IsOnceKeyUp(VK_LBUTTON))
			{
				if (PtInRect(&mCollisionRect, g_ptMouse))
				{
					(_scene->*_callback)();
				}
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

		switch (mState)
		{
		case Button::eButtonState::Idle:
			g.DrawImage(mpButtonIdleImage, mRenderPos.X, mRenderPos.Y, mSizeX, mSizeY);
			break;
		case Button::eButtonState::Hover:
			g.DrawImage(mpButtonPutImage, mRenderPos.X, mRenderPos.Y, mSizeX, mSizeY);
			break;
		case Button::eButtonState::Click:
			g.DrawImage(mpButtonClickImage, mRenderPos.X, mRenderPos.Y, mSizeX, mSizeY);
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

	int mSizeX = 0;
	int mSizeY = 0;
	Image* mpButtonIdleImage = nullptr;
	Image* mpButtonPutImage = nullptr;
	Image* mpButtonClickImage = nullptr;
	eButtonState mState = eButtonState::None;

	Point mRenderPos = {};
	RECT mCollisionRect = {};
};