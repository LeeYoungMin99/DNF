#include "stdafx.h"
#include "Image.h"

HRESULT Image::Init(LPCWCHAR path, const int& maxFrameX, const int& canCancelFrame, const int& correctX, const int& correctY, const float& animationSpeed, const bool& loop)
{
	_imageInfo = new IMAGE_INFO;

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

	gpRenderTarget->CreateBitmapFromWicBitmap(pConverter, nullptr, &(_imageInfo->_bitmap));

	pConverter->Release();
	pImageDecoder->Release();
	pFrameDecode->Release();

	D2D1_SIZE_F imageSize = _imageInfo->_bitmap->GetSize();
	D2D1_SIZE_F imageOneFrameSize = D2D1::SizeF(imageSize.width / maxFrameX, imageSize.height);

	_imageInfo->_maxFrameX = maxFrameX;
	_imageInfo->_canCancelFrame = canCancelFrame;
	_imageInfo->_imageFrameSize.width = imageOneFrameSize.width;
	_imageInfo->_imageFrameSize.height = imageOneFrameSize.height;
	_imageInfo->_animationSpeed = animationSpeed;
	_imageInfo->_bIsLoop = loop;
	_imageInfo->_correctX = correctX;
	_imageInfo->_correctY = correctY;

	return S_OK;
}
