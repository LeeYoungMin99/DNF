#include "stdafx.h"
#include "Animation.h"
#include "BmpImage.h"

HRESULT Animation::Init(AnimationData data)
{
	mpAnimationImage = new BmpImage;
	mpAnimationImage->Init(data.path, data.imageSizeX, data.imageSizeY, data.maxFrame, 1, true, RGB(255, 0, 255));
	mMaxFrame = data.maxFrame;
	mMotionSpeed = data.motionSpeed;
	mImageFrameSizeX = data.imageFrameSizeX;
	mImageFrameSizeY = data.imageFrameSizeY;
	mCorrectionPosX = data.correctionPosX;
	mCorrectionPosY = data.correctionPosY;
	mScale = data.scale;
	mbLoop = data.loop;

	return S_OK;
}

bool Animation::UpdateAnimation()
{
	mElapsedTime += DELTA_TIME;
	if (mElapsedTime >= mMotionSpeed)
	{
		mElapsedTime -= mMotionSpeed;
		++mCurrFrame;
		if (mCurrFrame >= mMaxFrame)
		{
			if (mbLoop)
			{
				mCurrFrame = 0;
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	return false;
}

void Animation::Render(HDC hdc, POINTFLOAT pos)
{
	mpAnimationImage->Render(hdc, (int)(pos.x + mCorrectionPosX), (int)(pos.y + mCorrectionPosY), mCurrFrame, 0, mScale);
}

void Animation::Release()
{
	SAFE_RELEASE(mpAnimationImage);
}

Animation* Animation::SetAnimation(AnimationData data)
{
	Animation* animation = new Animation;
	animation->Init(data);

	return animation;
}