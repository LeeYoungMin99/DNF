#include "stdafx.h"
#include "RectComponent.h"

#include "CameraManager.h"
#include "GameObject.h"
#include "Character.h"

void RectComponent::Update()
{
	LONG camX = CameraManager::GetSingleton()->GetX();
	LONG camY = CameraManager::GetSingleton()->GetY();
	LONG ownerX = mpOwner->GetPosition().x;
	LONG ownerY = mpOwner->GetPosition().y;
	Character::eDirX ownerDir = Character::eDirX::Right;

	if (dynamic_cast<Character*>(mpOwner))
	{
		if (((Character*)mpOwner)->GetDirX() != Character::eDirX::Right)
		{
			ownerDir = Character::eDirX::Left;
		}
	}

	mRect.left	 = ((int)ownerDir * mRectSize.left)		+ camX + ownerX;
	mRect.right  = ((int)ownerDir * mRectSize.right)	+ camX + ownerX;
	mRect.top	 =					mRectSize.top		+ camY + ownerY;
	mRect.bottom =					mRectSize.bottom	+ camY + ownerY;

	if (mRect.left > mRect.right)
	{
		std::swap(mRect.left, mRect.right);
	}
		
	if (Input::GetButtonDown('1'))
	{
		ChangeIsRender();
	}
}

void RectComponent::Render()
{
	if (mbIsRender)
	{
		ID2D1SolidColorBrush* mpBrush = nullptr;

		gpRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1, 1), &mpBrush);
		gpRenderTarget->DrawRectangle(D2D1::RectF((FLOAT)(mRect.left), (FLOAT)(mRect.top), (FLOAT)(mRect.right), (FLOAT)(mRect.bottom)), mpBrush, 1);
	}
}

void RectComponent::SetRect(RECT rect) noexcept
{
	mRect = rect;
}

void RectComponent::SetRectSize(RECT rect) noexcept
{
	mRectSize = rect;
}

const RECT* RectComponent::GetRectAddress() const noexcept
{
	return &mRect;
}

const RECT RectComponent::GetRect() const noexcept
{
	return mRect;
}

void RectComponent::ChangeIsRender() noexcept
{
	mbIsRender = !mbIsRender;
}
