#include "stdafx.h"
#include "AnimatorComponent.h"

#include "SpriteComponent.h"
#include "Character.h"
#include "Player.h"
#include "Image.h"
#include <typeinfo>

void AnimatorComponent::Init()
{
	PlayIdle();
}

void AnimatorComponent::Update()
{
	mElapsedTime += Timer::GetDeltaTime();

	if (mElapsedTime >= mAnimationSpeed)
	{
		mElapsedTime -= mAnimationSpeed;

		mpCurrSprite->mCurrFrame += 1;
		mCurrFrame = mpCurrSprite->mCurrFrame;
		if (mpCurrSprite->mCurrFrame >= mMaxFrameX)
		{
			if (mbIsLoop)
			{
				mpCurrSprite->mCurrFrame = 0;
			}
			else
			{
				PlayIdle();
			}
		}
	}
}

void AnimatorComponent::AddSprite(SpriteComponent* spriteComp, wstring tag)
{
	mpSprites.emplace(tag, spriteComp);
}

void AnimatorComponent::Play(wstring tag)
{
	if (mpCurrSprite != nullptr)
	{
		mpCurrSprite->mCurrFrame = 0;
		mCurrFrame = 0;
	}

	if ((mpCurrSprite = FindSprite(tag)) == nullptr)
	{
		PlayIdle();
	}

	mAnimationSpeed = mpCurrSprite->GetSprite()->GetAnimationSpeed();
	mMaxFrameX = mpCurrSprite->GetSprite()->GetMaxFrameX();
	mbIsLoop = mpCurrSprite->GetSprite()->GetIsLoop();
	mCurrSpriteTag = tag;
}


SpriteComponent* AnimatorComponent::FindSprite(wstring tag)
{
	auto it = mpSprites.find(tag);

	if (it == mpSprites.end())
	{
		return nullptr;
	}

	return it->second;
}

void AnimatorComponent::SetCurrFrame(int frame) noexcept
{
	mpCurrSprite->mCurrFrame = frame;
}

SpriteComponent* AnimatorComponent::GetCurrSprite() noexcept
{
	return mpCurrSprite;
}

wstring AnimatorComponent::GetCurrSpriteTag() noexcept
{
	return mCurrSpriteTag;
}

void AnimatorComponent::PlayIdle()
{
	if (dynamic_cast<Character*>(mpOwner))
	{
		if (((Character*)mpOwner)->GetDirX() == Character::eDirX::Left)
		{
			Play(L"LeftIdle");
			mCurrSpriteTag = L"LeftIdle";

			if (dynamic_cast<Player*>(mpOwner))
			{
				((Player*)mpOwner)->SetState(Character::eState::Idle);
				((Player*)mpOwner)->SetAttackType(Player::eAttackType::None);
			}
		}
		else
		{
			Play(L"RightIdle");
			mCurrSpriteTag = L"RightIdle";

			if (dynamic_cast<Player*>(mpOwner))
			{
				((Player*)mpOwner)->SetState(Character::eState::Idle);
				((Player*)mpOwner)->SetAttackType(Player::eAttackType::None);
			}
		}
	}
	else
	{
		Play(L"Idle");
		mCurrSpriteTag = L"Idle";
	}
}