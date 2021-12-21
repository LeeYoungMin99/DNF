#pragma once
#include "GameEntity.h"

#include "Image.h"
#include "ImageManager.h"
#include <functional>

class Image;
class ImageManager;
class Animation : public GameEntity
{
public:
	Animation(const wstring path, int animTag, bool(*callback)())
	{
		mpImage = ImageManager::GetSingleton()->FindImage(path);
		mAnimTag = animTag;

		mMaxFrame = mpImage->GetMaxFrameX();
		mAnimationSpeed = mpImage->GetAnimationSpeed();
		mbIsLoop = mpImage->GetIsLoop();

		mpCallback = callback;
	}

	virtual ~Animation() noexcept = default;

	virtual void Init() override {}
	virtual void Render() override {}
	virtual void Release() override {}

	virtual void Update() override
	{
		if (mbIsEnd) { return; }

		mElapsedTime += Timer::GetDeltaTime();

		if (mElapsedTime >= mAnimationSpeed)
		{
			mElapsedTime -= mAnimationSpeed;

			++mCurrFrame;

			if (mMaxFrame == mCurrFrame)
			{
				if (mbIsLoop)
				{
					mCurrFrame = 0;
				}
				else
				{
					mbIsEnd = true;
				}
			}
		}
	}

	int GetAnimTag() const noexcept { return mAnimTag; }
	int GetCurrFrame() const noexcept { return mCurrFrame; }
	bool GetIsEnd() const noexcept { return mbIsEnd; }
	Image* GetImage() const noexcept { return mpImage; }

	bool CanChange() const
	{
		return mpCallback;
	}

private:
	bool(*mpCallback)() = nullptr;
	Image* mpImage = nullptr;
	int mAnimTag = 0;

	int mCurrFrame = 0;
	int mMaxFrame = 0;

	float mElapsedTime = 0.0f;
	float mAnimationSpeed = 0.0f;

	bool mbIsLoop = false;
	bool mbIsEnd = false;
};

