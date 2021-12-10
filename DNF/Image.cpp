#include "stdafx.h"
#include "Image.h"

HRESULT Image::Init(LPCWCHAR path, int maxFrameX, int maxFrameY, float animationSpeed, bool loop)
{
	imageInfo = new IMAGE_INFO;

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

	gpRenderTarget->CreateBitmapFromWicBitmap(pConverter, nullptr, &(imageInfo->pBitmap));

	pConverter->Release();
	pImageDecoder->Release();
	pFrameDecode->Release();

	D2D1_SIZE_F imageSize = imageInfo->pBitmap->GetSize();
	D2D1_SIZE_F imageOneFrameSize = D2D1::SizeF(imageSize.width / maxFrameX, imageSize.height / maxFrameY);

	imageInfo->maxFrameX = maxFrameX;
	imageInfo->maxFrameY = maxFrameY;
	imageInfo->imageFrameSize.width = imageOneFrameSize.width;
	imageInfo->imageFrameSize.height = imageOneFrameSize.height;
	imageInfo->animationSpeed = animationSpeed;
	imageInfo->bIsLoop = loop;

	return S_OK;
}

void Image::Release()
{
	SAFE_DELETE(imageInfo);
}

ID2D1Bitmap* Image::GetBitmap() noexcept
{
	return imageInfo->pBitmap;
}

int Image::GetMaxFrameX() const noexcept
{
	return imageInfo->maxFrameX;
}

int Image::GetMaxFrameY() const noexcept
{
	return imageInfo->maxFrameY;
}

D2D1_SIZE_F Image::GetImageFrameSize() const noexcept
{
	return imageInfo->imageFrameSize;
}

float Image::GetAnimationSpeed() const noexcept
{
	return imageInfo->animationSpeed;
}

bool Image::GetIsLoop() const noexcept
{
	return imageInfo->bIsLoop;
}
