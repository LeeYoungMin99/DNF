#include "stdafx.h"
#include "AnimatorComponent.h"

#include "SpriteComponent.h"
#include "Character.h"
#include "Player.h"
#include "Image.h"
#include <typeinfo>

void AnimatorComponent::Init()
{
	mpCurrSprite = FindSprite(L"Idle");
	mAnimationSpeed = mpCurrSprite->GetSprite()->GetAnimationSpeed();
	mMaxFrameX = mpCurrSprite->GetSprite()->GetMaxFrameX();
	mbIsLoop = mpCurrSprite->GetSprite()->GetIsLoop();
	mCurrSpriteTag = L"Idle";
}

void AnimatorComponent::Update()
{
	if (mbPause)
		return;

	mElapsedTime += Timer::GetDeltaTime();

	if (mElapsedTime >= mAnimationSpeed)
	{
		mElapsedTime -= mAnimationSpeed;

		mpCurrSprite->SetNextFrame();
		if (mpCurrSprite->GetCurrFrame() >= mMaxFrameX)
		{
			if (mbIsLoop)
			{
				mpCurrSprite->SetCurrFrame(0);
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
		mpCurrSprite->SetCurrFrame(0);
	}

	mpCurrSprite = FindSprite(tag);
	mAnimationSpeed = mpCurrSprite->GetSprite()->GetAnimationSpeed();
	mMaxFrameX = mpCurrSprite->GetSprite()->GetMaxFrameX();
	mbIsLoop = mpCurrSprite->GetSprite()->GetIsLoop();
	mCurrSpriteTag = tag;
}

void AnimatorComponent::Pause()
{
	mbPause = true;
}

//struct AnimInfo
//{
//	float AnimationSpeed;
//	int MaxFrameX;
//	bool IsLoop;
//	wstring Tag;
//};

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
	mpCurrSprite->SetCurrFrame(frame);
}

SpriteComponent* AnimatorComponent::GetCurrSprite() noexcept
{
	return mpCurrSprite;
}

wstring AnimatorComponent::GetCurrSpriteTag() noexcept
{
	return mCurrSpriteTag;
}

int AnimatorComponent::GetCurrFrame() noexcept
{
	return mpCurrSprite->GetCurrFrame();
}

void AnimatorComponent::PlayIdle()
{
	Play(L"Idle");
	mCurrSpriteTag = L"Idle";

	if (dynamic_cast<Player*>(mpOwner))
	{
		((Player*)mpOwner)->SetState(Character::eState::Idle);
		((Player*)mpOwner)->SetAttackType(Player::eAttackType::None);
	}
}