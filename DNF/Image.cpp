#include "stdafx.h"
#include "Image.h"

HRESULT Image::Init(LPCWCHAR path, int maxFrameX, int correctX, int correctY, float animationSpeed, bool loop)
{
	mpImageInfo = new IMAGE_INFO;

	IWICFormatConverter* pConverter = nullptr;
	IWICBitmapDecoder* pImageDecoder = nullptr;
	IWICBitmapFrameDecode* pFrameDecode = nullptr;

	gpImagingFactory->CreateDecoderFromFilename(path,
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&pImageDecoder);
	pImageDecoder->GetFrame(0, &pFrameDecode);

	gpImagingFactory->CreateFormatConverter(&pConverter);
	pConverter->Initialize(pFrameDecode,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom);

	gpRenderTarget->CreateBitmapFromWicBitmap(pConverter, nullptr, &(mpImageInfo->pBitmap));

	pConverter->Release();
	pImageDecoder->Release();
	pFrameDecode->Release();

	D2D1_SIZE_F imageSize = mpImageInfo->pBitmap->GetSize();
	D2D1_SIZE_F imageOneFrameSize = D2D1::SizeF(imageSize.width / maxFrameX, imageSize.height);

	mpImageInfo->maxFrameX = maxFrameX;
	mpImageInfo->imageFrameSize.width = imageOneFrameSize.width;
	mpImageInfo->imageFrameSize.height = imageOneFrameSize.height;
	mpImageInfo->animationSpeed = animationSpeed;
	mpImageInfo->bIsLoop = loop;
	mpImageInfo->correctX = correctX;
	mpImageInfo->correctY = correctY;

	return S_OK;
}

void Image::Render(int x, int y)
{
	LONG posX = x;
	LONG posY = y;
	FLOAT imageFrameSizeX = mpImageInfo->imageFrameSize.width;
	FLOAT imageFrameSizeY = mpImageInfo->imageFrameSize.height;
	FLOAT renderSizeX = posX + imageFrameSizeX;
	FLOAT renderSizeY = posY + imageFrameSizeY;

	gpRenderTarget->DrawBitmap(mpImageInfo->pBitmap
		, D2D1::RectF((FLOAT)posX, (FLOAT)posY, renderSizeX, renderSizeY)
		, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
		, D2D1::RectF(0, 0, imageFrameSizeX, imageFrameSizeY));
}

void Image::Release()
{
	SAFE_DELETE(mpImageInfo);
}

ID2D1Bitmap* Image::GetBitmap() noexcept
{
	return mpImageInfo->pBitmap;
}

int Image::GetMaxFrameX() const noexcept
{
	return mpImageInfo->maxFrameX;
}

D2D1_SIZE_F Image::GetImageFrameSize() const noexcept
{
	return mpImageInfo->imageFrameSize;
}

float Image::GetAnimationSpeed() const noexcept
{
	return mpImageInfo->animationSpeed;
}

bool Image::GetIsLoop() const noexcept
{
	return mpImageInfo->bIsLoop;
}

int Image::GetCorrectX() const noexcept
{
	return mpImageInfo->correctX;
}

int Image::GetCorrectY() const noexcept
{
	return mpImageInfo->correctY;
}
