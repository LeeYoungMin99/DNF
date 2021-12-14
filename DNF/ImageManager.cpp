#include "stdafx.h"
#include "ImageManager.h"
#include "Image.h"

ImageManager::~ImageManager()
{
	for (auto& elem : mpImages)
	{
		SAFE_RELEASE(elem.second);
	}

	mpImages.clear();
}

void ImageManager::Init()
{
	AddImage(L"Image/Button/SmallButton.png", 3, 1);
	AddImage(L"Image/Button/LargeButton.png", 3, 1);

	AddImage(L"Image/CharacterSelectScene/Background.png", 1, 1);
	AddImage(L"Image/CharacterSelectScene/SlotBackground.png", 1, 1);

	AddImage(L"Image/CharacterMotion/Player/Left/Idle.png", 33, -245, -374, 0.2f, true);
	AddImage(L"Image/CharacterMotion/Player/Right/Idle.png", 33, -245, -374, 0.2f, true);
	AddImage(L"Image/CharacterMotion/Player/Left/Walk.png", 10, -245, -374, 0.1f, true);
	AddImage(L"Image/CharacterMotion/Player/Right/Walk.png", 10, -245, -374, 0.1f, true);
	AddImage(L"Image/CharacterMotion/Player/Left/Run.png", 8, -245, -374, 0.1f, true);
	AddImage(L"Image/CharacterMotion/Player/Right/Run.png", 8, -245, -374, 0.1f, true);

	AddImage(L"Image/CharacterMotion/Player/Left/NormalAttack1.png", 5, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Right/NormalAttack1.png", 5, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Left/NormalAttack2.png", 6, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Right/NormalAttack2.png", 6, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Left/NormalAttack3.png", 6, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Right/NormalAttack3.png", 6, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Left/NormalAttack4.png", 5, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Right/NormalAttack4.png", 5, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Left/NormalAttack5.png", 5, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Right/NormalAttack5.png", 5, -245, -374, 0.1f);

	AddImage(L"Image/CharacterMotion/Player/Left/DashAttack2.png", 6, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Right/DashAttack2.png", 6, -245, -374, 0.1f);

	AddImage(L"Image/CharacterMotion/Player/Left/Jump.png", 19, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Right/Jump.png", 19, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Left/JumpDownIdle.png", 2, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Right/JumpDownIdle.png", 2, -245, -374, 0.1f);

	AddImage(L"Image/CharacterMotion/Player/Left/JumpAttack.png", 13, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Right/JumpAttack.png", 13, -245, -374, 0.1f);
}

Image* ImageManager::AddImage(const wchar_t* path, int maxFrameX, int correctX, int correctY, float animationSpeed, bool loop)
{
	Image* img = FindImage(path);

	if (img != nullptr)
	{
		return img;
	}

	img = new Image;

	if (FAILED(img->Init(path, maxFrameX, correctX, correctY, animationSpeed, loop)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mpImages.emplace(path, img);

	return img;
}

Image* ImageManager::FindImage(wstring path)
{
	auto it = mpImages.find(path);

	if (it == mpImages.end())
	{
		return nullptr;
	}

	return it->second;
}
