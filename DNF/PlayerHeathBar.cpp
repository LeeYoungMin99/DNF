#include "stdafx.h"
#include "PlayerHeathBar.h"

#include "Image.h"
#include "ImageManager.h"

PlayerHealthBar::PlayerHealthBar(const wstring path, POINT pos) noexcept
{
	mpHealthBar = ImageManager::GetSingleton()->FindImage(path);
	mPos = pos;
}

void PlayerHealthBar::Init()
{
}

void PlayerHealthBar::Update()
{
}

void PlayerHealthBar::Render()
{
	LONG posX = mPos.x;
	LONG posY = mPos.y;
	FLOAT imageFrameSizeX = mpHealthBar->GetImageFrameSize().width;
	FLOAT imageFrameSizeY = mpHealthBar->GetImageFrameSize().height;
	FLOAT renderSizeX = posX + imageFrameSizeX;
	FLOAT renderSizeY = posY + imageFrameSizeY;

	FLOAT reamainingAmount = imageFrameSizeY * ((100.0f - mRemainingAmount) * 0.01);

	gpRenderTarget->DrawBitmap(mpHealthBar->GetBitmap()
		, D2D1::RectF((FLOAT)posX, (FLOAT)posY + reamainingAmount, renderSizeX, renderSizeY)
		, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
		, D2D1::RectF(0, reamainingAmount, imageFrameSizeX, imageFrameSizeY));
}

void PlayerHealthBar::Release()
{
}

void PlayerHealthBar::SetRemainingAmount(float value) noexcept
{
	mRemainingAmount = value;
}