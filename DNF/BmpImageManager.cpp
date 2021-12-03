#include "stdafx.h"
#include "BmpImageManager.h"
#include "BmpImage.h"

void BmpImageManager::Init()
{
}

void BmpImageManager::Release()
{
	for (auto& elem : images)
	{
		SAFE_RELEASE(elem.second);
	}

	images.clear();
}

BmpImage* BmpImageManager::AddImage(const char* path, int width, int height, bool isTrans, COLORREF transColor)
{
	BmpImage* img = FindImage(path);

	if (img)
	{
		return img;
	}

	img = new BmpImage;

	if (FAILED(img->Init(path, width, height, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	images.emplace(path, img);

	return img;
}

BmpImage* BmpImageManager::AddImage(const char* path, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	BmpImage* img = FindImage(path);

	if (img)
	{
		return img;
	}

	img = new BmpImage;

	if (FAILED(img->Init(path, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	images.emplace(path, img);

	return img;
}

BmpImage* BmpImageManager::FindImage(const char* fileName)
{
	auto it = images.find(fileName);
	if (it == images.end())
	{
		return nullptr;
	}

	return it->second;
}