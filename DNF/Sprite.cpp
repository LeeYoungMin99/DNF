#include "stdafx.h"
#include "Sprite.h"

#include "Image.h"
#include "ImageManager.h"
#include "CameraManager.h"

Sprite::Sprite(const wstring& path, Scene* scene, const std::wstring& tag, int order)
	:GameObject(scene, tag), _order{ order }
{
	_image = ImageManager::GetSingleton()->FindImage(path);
	AddY(-order);
}

void Sprite::Render()
{
	LONG posX = GetX() + CameraManager::GetSingleton()->GetX();
	LONG posY = GetY() + CameraManager::GetSingleton()->GetY() + _order;
	FLOAT imageFrameSizeX = _image->GetImageFrameSize().width;
	FLOAT imageFrameSizeY = _image->GetImageFrameSize().height;
	FLOAT renderSizeX = posX + imageFrameSizeX;
	FLOAT renderSizeY = posY + imageFrameSizeY;

	gpRenderTarget->DrawBitmap(_image->GetBitmap()
		, D2D1::RectF((FLOAT)posX, (FLOAT)posY, renderSizeX, renderSizeY)
		, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
		, D2D1::RectF(0, 0, imageFrameSizeX, imageFrameSizeY));
}

void Sprite::SetImage(Image* img)
{
	_image = img;
}
