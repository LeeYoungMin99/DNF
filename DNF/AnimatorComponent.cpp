#include "stdafx.h"
#include "AnimatorComponent.h"

#include "SpriteComponent.h"
#include "Image.h"

void AnimatorComponent::Update()
{
	mElapsedTime += Timer::GetDeltaTime();

	if (mElapsedTime >= mAnimationSpeed)
	{
		currSprite->currFrameX += 1;

		if (currSprite->currFrameX > mMaxFrameX)
		{
			if (mbIsLoop)
			{
				currSprite->currFrameX = 0;
			}
			else
			{
				Stop(L"Idle");
			}
		}
	}
}

void AnimatorComponent::AddSprite(SpriteComponent* spriteComp, wstring tag)
{
	mSprites.emplace(tag, spriteComp);
}

void AnimatorComponent::Play(wstring tag)
{
	if ((currSprite = FindSprite(tag)) == nullptr)
	{
		Play(L"Idle");
	}

	mAnimationSpeed = currSprite->GetSprite()->GetAnimationSpeed();
	mMaxFrameX = currSprite->GetSprite()->GetMaxFrameX();
	mMaxFrameY = currSprite->GetSprite()->GetMaxFrameY();
	mbIsLoop = currSprite->GetSprite()->GetIsLoop();
}

void AnimatorComponent::Stop(wstring tag)
{
	currSprite->currFrameX = 0;
	currSprite->currFrameY = 0;

	if ((currSprite = FindSprite(tag)) == nullptr)
	{
		Play(L"Idle");
	}
}

SpriteComponent* AnimatorComponent::FindSprite(wstring tag)
{
	auto it = mSprites.find(tag);

	if (it == mSprites.end())
	{
		return nullptr;
	}

	return it->second;
}

SpriteComponent* AnimatorComponent::GetCurrSprite()
{
	return currSprite;
}
