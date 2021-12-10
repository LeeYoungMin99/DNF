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
		ID2D1SolidColorBrush* pBrush = nullptr;
		gpRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1, 1), &pBrush);
		gpRenderTarget->DrawRectangle(D2D1::RectF((FLOAT)(mRect.left), (FLOAT)(mRect.top), (FLOAT)(mRect.right), (FLOAT)(mRect.bottom)), pBrush, 10);
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

const RECT* RectComponent::GetRectAddress() const
{
	return &mRect;
}
