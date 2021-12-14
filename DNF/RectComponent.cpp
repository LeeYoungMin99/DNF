#include "stdafx.h"
#include "RectComponent.h"

void RectComponent::Update()
{
	if (Input::GetButtonDown('1'))
	{
		if (mbIsRender) { TurnoffRender(); }
		else { TurnonRender(); }
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

void RectComponent::TurnoffRender() noexcept
{
	mbIsRender = false;
}

void RectComponent::TurnonRender() noexcept
{
	mbIsRender = true;
}

void RectComponent::SetRect(RECT rect) noexcept
{
	mRect = rect;
}

const RECT* RectComponent::GetRectAddress() const noexcept
{
	return &mRect;
}

const RECT RectComponent::GetRect() const noexcept
{
	return mRect;
}