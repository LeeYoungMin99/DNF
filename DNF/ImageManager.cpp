#include "stdafx.h"
#include "ImageManager.h"
#include "Image.h"

ImageManager::~ImageManager() noexcept
{
	for (auto& elem : images)
	{
		SAFE_RELEASE(elem.second);
	}

	images.clear();
}

void ImageManager::Init()
{
	AddImage(L"Image/Button/SmallButton.png", 3, 1);
	AddImage(L"Image/Button/LargeButton.png", 3, 1);
}

Image* ImageManager::AddImage(const wchar_t* path, int maxFrameX, int maxFrameY, float animationSpeed)
{
	Image* img = FindImage(path);

	if (img != nullptr)
	{
		return img;
	}

	img = new Image;

	if (FAILED(img->Init(path, maxFrameX, maxFrameY, animationSpeed)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	images.emplace(path, img);

	return img;
}

Image* ImageManager::FindImage(wstring fileName)
{
	auto it = images.find(fileName);

	if (it == images.end())
	{
		return nullptr;
	}

	return it->second;
}
