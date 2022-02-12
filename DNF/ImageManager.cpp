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

	AddImage(L"Image/NPC_ClickNameSpace.png", 1);
	AddImage(L"Image/NPC_ClickButtonHover.png", 1);
	AddImage(L"Image/NPC_ClickButtonIdle.png", 1);

	AddImage(L"Image/CharacterMotion/Seria/Idle.png", 12, 12, -27, -116, 0.2f, true);
	AddImage(L"Image/CharacterMotion/Seria/Hover.png", 12, 12, -28, -117, 0.2f, true);

#pragma region Vinoshu

	AddImage(L"Image/CharacterMotion/Vinoshu/Idle.png", 8, 8, -64, -126, 0.15f, true);
	AddImage(L"Image/CharacterMotion/Vinoshu/Casting.png", 11, 11, -88, -156, 0.1f);
	AddImage(L"Image/CharacterMotion/Vinoshu/ForwardWalk.png", 8, 8, -63, -98, 0.08f, true);
	AddImage(L"Image/CharacterMotion/Vinoshu/BackwardWalk.png", 8, 8, -74, -111, 0.08f, true);
	AddImage(L"Image/CharacterMotion/Vinoshu/NormalAttack.png", 10, 10, -122, -162, 0.08f);

	AddImage(L"Image/CharacterMotion/Vinoshu/Damaged.png", 1, 1, -64, -120, 2.0f);
	AddImage(L"Image/CharacterMotion/Vinoshu/Down.png", 1, 1, -71, -39, 2.0f);
	AddImage(L"Image/CharacterMotion/Vinoshu/DownIdle.png", 1, 1, -47, -131, 1.0f);
	AddImage(L"Image/CharacterMotion/Vinoshu/JumpDamagedBounce.png", 1, 1, -63, -65, 1.0f);
	AddImage(L"Image/CharacterMotion/Vinoshu/LowJumpDamaged.png", 1, 1, -52, -125, 1.0f);
	AddImage(L"Image/CharacterMotion/Vinoshu/HighJumpDamaged.png", 1, 1, -55, -122, 1.0f);

	AddImage(L"Image/CharacterMotion/Meteor/MagicCircle.png", 10, 10, -53, 61, 0.1f);
	AddImage(L"Image/CharacterMotion/Meteor/Falling.png", 6, 6, -80, -185, 0.1f, true);
	AddImage(L"Image/CharacterMotion/Meteor/Explosion.png", 13, 13, -255, -145, 0.1f);

#pragma endregion

#pragma region Player

	AddImage(L"Image/CharacterMotion/Player/Idle.png", 33, 33, -245, -374, 0.2f, true);
	AddImage(L"Image/CharacterMotion/Player/Walk.png", 10, 33, -245, -374, 0.1f, true);
	AddImage(L"Image/CharacterMotion/Player/Run.png", 8, 33, -245, -374, 0.1f, true);

	AddImage(L"Image/CharacterMotion/Player/Damaged.png", 1, 1, -245, -374, 2.0f);
	AddImage(L"Image/CharacterMotion/Player/Down.png", 1, 1, -245, -374, 2.0f);
	AddImage(L"Image/CharacterMotion/Player/DownIdle.png", 1, 1, -245, -374, 1.0f);
	AddImage(L"Image/CharacterMotion/Player/JumpDamagedBounce.png", 1, 1, -245, -374, 1.0f);
	AddImage(L"Image/CharacterMotion/Player/LowJumpDamaged.png", 1, 1, -245, -374, 1.0f);
	AddImage(L"Image/CharacterMotion/Player/HighJumpDamaged.png", 1, 1, -245, -374, 1.0f);


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

