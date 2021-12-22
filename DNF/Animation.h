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
	Animation(const wstring& path, const wstring& animTag)
	{
		mpImage = ImageManager::GetSingleton()->FindImage(path);
		mAnimTag = animTag;

		mMaxFrame = mpImage->GetMaxFrameX();
		mAnimationSpeed = mpImage->GetAnimationSpeed();
		mbIsLoop = mpImage->GetIsLoop();

		if (mbIsLoop) { mbIsEnd = true; }
	}

	virtual ~Animation() noexcept = default;

	virtual void Init() override {}
	virtual void Render() override {}
	virtual void Release() override {}

	virtual void Update() override
	{
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

	wstring GetAnimTag() const noexcept { return mAnimTag; }
	Image* GetImage() const noexcept { return mpImage; }
	int GetCurrFrame() const noexcept { return mCurrFrame; }
	bool GetIsLoop() const noexcept { return mbIsLoop; }
	bool IsEnd() const noexcept { return mbIsEnd; }

	void SetCurrFrame(int frame) noexcept { mCurrFrame = frame; }
	void SetIsEnd(bool b) noexcept { mbIsEnd = b; }
private:
	Image* mpImage = nullptr;
	wstring mAnimTag = {};

	int mCurrFrame = 0;
	int mMaxFrame = 0;

	float mElapsedTime = 0.0f;
	float mAnimationSpeed = 0.0f;

	bool mbIsLoop = false;
	bool mbIsEnd = false;
};

