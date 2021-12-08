#pragma once
#include "GameObject.h"

template <typename Type>
class Button : public GameObject
{
private:
	using t = Type;
	using callback_t = void(Type::*)();

public:
	enum class eButtonState { Idle, Hover, Click, None, };
	enum class eButtonType { GameObject, Scene, None, };

	Button(t* type, callback_t callback)
		: GameObject()
	{
		if (is_base_of_v<Scene, Type>) { mType = eButtonType::Scene; }
		else if (is_base_of_v<GameObject, Type>) { mType = eButtonType::GameObject; }
		else { static_assert(true, "버튼 이닛할때 잘못넣음"); }

		mpType = type;
		mpCallback = callback;
	}
	virtual ~Button() = default;

	HRESULT Init(eButtonType type, POINT pos, int sizeX, int sizeY)
	{
		this->mPos = { float(pos.x),float(pos.y) };

		TCHAR str[50] = {};
		TCHAR str1[50] = {};
		TCHAR str2[50] = {};
		wcsncpy(str, L"Image/Button/", 13);
		wcscat(str, L"SmallButton");
		wcscat(str, L"PutImage.png");

		switch (type)
		{
		case eButtonType::Scene:
			this->mpButtonIdleImage = FROM_FILE(L"Image/Button/SmallButtonIdleImage.png");
			this->mpButtonPutImage = FROM_FILE(str);
			this->mpButtonClickImage = FROM_FILE(L"Image/Button/SmallButtonClickImage.png");
			break;
		case eButtonType::GameObject:
			this->mpButtonIdleImage = FROM_FILE(L"Image/Button/SmallButtonIdleImage.png");
			this->mpButtonPutImage = FROM_FILE(L"Image/Button/SmallButtonPutImage.png");
			this->mpButtonClickImage = FROM_FILE(L"Image/Button/SmallButtonClickImage.png");
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
			if (PtInRect(&mCollisionRect, Input::GetMousePosition()))
				mState = eButtonState::Hover;
			break;
		case Button::eButtonState::Hover:
			if (false == PtInRect(&mCollisionRect, Input::GetMousePosition()))
				mState = eButtonState::Idle;

			if (Input::GetButton(VK_LBUTTON))
				mState = eButtonState::Click;
			break;
		case Button::eButtonState::Click:
			if (false == PtInRect(&mCollisionRect, Input::GetMousePosition()))
				mState = eButtonState::Idle;

			if (Input::GetButtonUp(VK_LBUTTON))
			{
				if (PtInRect(&mCollisionRect, Input::GetMousePosition()))
				{
					(mpType->*mpCallback)();
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
	t* mpType;
	callback_t mpCallback;

	int mSizeX = 0;
	int mSizeY = 0;
	Image* mpButtonIdleImage = nullptr;
	Image* mpButtonPutImage = nullptr;
	Image* mpButtonClickImage = nullptr;
	eButtonState mState = eButtonState::None;
	eButtonType mType = eButtonType::None;

	Point mRenderPos = {};
	RECT mCollisionRect = {};
};