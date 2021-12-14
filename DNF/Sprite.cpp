#include "stdafx.h"
#include "Sprite.h"

#include "Image.h"

void Sprite::Render()
{
	LONG posX = GetX();
	LONG posY = GetY();
	FLOAT imageFrameSizeX = mpImage->GetImageFrameSize().width;
	FLOAT imageFrameSizeY = mpImage->GetImageFrameSize().height;
	FLOAT renderSizeX = posX + imageFrameSizeX;
	FLOAT renderSizeY = posY + imageFrameSizeY;

	gpRenderTarget->DrawBitmap(mpImage->GetBitmap()
		, D2D1::RectF((FLOAT)posX, (FLOAT)posY, renderSizeX, renderSizeY)
		, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
		, D2D1::RectF(0, 0, imageFrameSizeX, imageFrameSizeY));
}

void Sprite::SetImage(Image* img)
{
	mpImage = img;
}
