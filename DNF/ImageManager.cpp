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
	AddImage(L"Image/Button/SmallButtonIdle.png", 1);
	AddImage(L"Image/Button/SmallButtonHover.png", 1);
	AddImage(L"Image/Button/SmallButtonClick.png", 1);
	AddImage(L"Image/Button/StartButtonIdle.png", 1);
	AddImage(L"Image/Button/StartButtonHover.png", 1);
	AddImage(L"Image/Button/StartButtonClick.png", 1);


	AddImage(L"Image/CharacterMotion/Seria/Idle.png", 12, -27, -116, 0.2f, true);
	AddImage(L"Image/CharacterMotion/Seria/Hover.png", 12, -28, -117, 0.2f, true);

	// UI
	AddImage(L"Image/UI/PlayerStatus.png", 1, -166, -75);
	AddImage(L"Image/UI/HP.png", 1);
	AddImage(L"Image/UI/MP.png", 1);

	AddImage(L"Image/CharacterSelectScene/Background.png", 1);
	AddImage(L"Image/CharacterSelectScene/SlotBackground.png", 1);

	AddImage(L"Image/Elvengard/SeriaRoom/Background.png", 1);

	AddImage(L"Image/CharacterMotion/Player/Idle.png", 33, -245, -374, 0.2f, true);
	AddImage(L"Image/CharacterMotion/Player/Walk.png", 10, -245, -374, 0.1f, true);
	AddImage(L"Image/CharacterMotion/Player/Run.png", 8, -245, -374, 0.1f, true);

	AddImage(L"Image/CharacterMotion/Player/NormalAttack1.png", 5, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/NormalAttack2.png", 6, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/NormalAttack3.png", 6, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/NormalAttack4.png", 5, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/NormalAttack5.png", 5, -245, -374, 0.1f);

	AddImage(L"Image/CharacterMotion/Player/DashAttack2.png", 6, -245, -374, 0.1f);

	AddImage(L"Image/CharacterMotion/Player/Jump.png", 19, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/JumpDownIdle.png", 2, -245, -374, 0.1f);

	AddImage(L"Image/CharacterMotion/Player/JumpAttack.png", 13, -245, -374, 0.1f);
}

void ImageManager::Update()
{
}

void ImageManager::Render()
{
}

void ImageManager::Release()
{
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

