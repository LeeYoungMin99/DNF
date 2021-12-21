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
	if (mbIsPause)
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
	if (mpCurrSprite)
	{

		mpCurrSprite->SetCurrFrame(0);
	}

	mbIsPause = false;
	mpCurrSprite = FindSprite(tag);
	mAnimationSpeed = mpCurrSprite->GetSprite()->GetAnimationSpeed();
	mMaxFrameX = mpCurrSprite->GetSprite()->GetMaxFrameX();
	mbIsLoop = mpCurrSprite->GetSprite()->GetIsLoop();
	mCurrSpriteTag = tag;
	mElapsedTime = 0.0f;
}

void AnimatorComponent::Pause()
{
	mbIsPause = true;
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

bool AnimatorComponent::GetIsPause() const noexcept
{
	return mbIsPause;
}

int AnimatorComponent::GetCurrFrame() const noexcept
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