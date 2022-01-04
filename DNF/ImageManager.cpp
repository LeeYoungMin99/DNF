#include "stdafx.h"
#include "ImageManager.h"
#include "Image.h"

ImageManager::~ImageManager()
{
	for (auto& elem : _images)
	{
		SAFE_RELEASE(elem.second);
	}

	_images.clear();
}

void ImageManager::Init()
{
	AddImage(L"Image/Elvengard/SeriaRoom/Background.png", 1);
	AddImage(L"Image/Elvengard/BattleScene/FarBackground.png", 1);
	AddImage(L"Image/Elvengard/BattleScene/MiddleBackground.png", 1);
	AddImage(L"Image/Elvengard/BattleScene/Tile.png", 1);

	AddImage(L"Image/CharacterMotion/Seria/Idle.png", 12, 12, -27, -116, 0.2f, true);
	AddImage(L"Image/CharacterMotion/Seria/Hover.png", 12, 12, -28, -117, 0.2f, true);

#pragma region Hanier

	AddImage(L"Image/CharacterMotion/Hanier/Idle.png", 8, 8, -106, -278, 0.15f, true);
	AddImage(L"Image/CharacterMotion/Hanier/Walk.png", 6, 6, -192, -140, 0.08f, true);
	
#pragma endregion

#pragma region Player

	AddImage(L"Image/CharacterMotion/Player/Idle.png", 33, 33, -245, -374, 0.2f, true);
	AddImage(L"Image/CharacterMotion/Player/Walk.png", 10, 33, -245, -374, 0.1f, true);
	AddImage(L"Image/CharacterMotion/Player/Run.png", 8, 33, -245, -374, 0.1f, true);
	AddImage(L"Image/CharacterMotion/Player/Jump1.png", 2, 2, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Jump2.png", 1, 1, -245, -374, 0.1f);
	AddImage(L"Image/CharacterMotion/Player/Jump3.png", 2, 2, -245, -374, 0.1f, true);
	AddImage(L"Image/CharacterMotion/Player/JumpDownIdle.png", 1, 1, -245, -374, 0.1f);

	AddImage(L"Image/CharacterMotion/Player/NormalAttack1.png", 5, 4, -245, -374, 0.08f);
	AddImage(L"Image/CharacterMotion/Player/NormalAttack2.png", 6, 5, -245, -374, 0.08f);
	AddImage(L"Image/CharacterMotion/Player/NormalAttack3.png", 6, 5, -245, -374, 0.08f);
	AddImage(L"Image/CharacterMotion/Player/NormalAttack4.png", 5, 4, -245, -374, 0.08f);
	AddImage(L"Image/CharacterMotion/Player/NormalAttack5.png", 5, 4, -245, -374, 0.08f);

	AddImage(L"Image/CharacterMotion/Player/DashAttackEnd.png", 6, 6, -245, -374, 0.1f);

	AddImage(L"Image/CharacterMotion/Player/JumpAttack.png", 8, 8, -245, -374, 0.08f);

	AddImage(L"Image/CharacterMotion/Player/UpperSlash.png", 6, 6, -245, -374, 0.09f);
	AddImage(L"Image/CharacterMotion/Player/SnakeDance.png", 18, 18, -352, -374, 0.08f);
#pragma endregion
}

Image* ImageManager::AddImage(const wchar_t* path, const int& maxFrameX, const int& canCancelFrame, const int& correctX, const int& correctY, const float& animationSpeed, const bool& loop)
{
	Image* img = FindImage(path);

	if (img != nullptr)
	{
		return img;
	}

	img = new Image;

	if (FAILED(img->Init(path, maxFrameX, canCancelFrame, correctX, correctY, animationSpeed, loop)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	_images.emplace(path, img);

	return img;
}

Image* ImageManager::FindImage(const wstring& path)
{
	auto it = _images.find(path);

	if (it == _images.end())
	{
		return nullptr;
	}

	return it->second;
}

