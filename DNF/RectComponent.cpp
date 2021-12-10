#include "stdafx.h"
#include "RectComponent.h"

void RectComponent::Update()
{
	if (Input::GetButtonDown('1'))
	{
		if (mbIsRender) { TurnoffRender(); }
		else			{ TurnonRender(); }
	}
}

void RectComponent::Render(HDC hdc)
{
	if (mbIsRender)
	{
		Rectangle(hdc, mRect.left, mRect.top, mRect.right, mRect.bottom);
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

RECT RectComponent::GetRect() const
{
	return mRect;
}
