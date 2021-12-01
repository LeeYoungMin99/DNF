#include "stdafx.h"
#include "Animation.h"
#include "BmpImage.h"

HRESULT Animation::Init(AnimationData data)
{
	animationImage = new BmpImage;
	animationImage->Init(data.path, data.imageSizeX, data.imageSizeY, data.maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = data.maxFrame;
	motionSpeed = data.motionSpeed;
	imageFrameSizeX = data.imageFrameSizeX;
	imageFrameSizeY = data.imageFrameSizeY;
	correctionPosX = data.correctionPosX;
	correctionPosY = data.correctionPosY;
	scale = data.scale;
	loop = data.loop;

	return S_OK;
}

bool Animation::UpdateAnimation()
{
	elapsedTime += DELTA_TIME;
	if (elapsedTime >= motionSpeed)
	{
		elapsedTime -= motionSpeed;
		++currFrame;
		if (currFrame >= maxFrame)
		{
			if (loop)
			{
				currFrame = 0;
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
	animationImage->Render(hdc, pos.x - correctionPosX, pos.y, currFrame, 0, scale);
}

void Animation::Release()
{
	SAFE_RELEASE(animationImage);
}
