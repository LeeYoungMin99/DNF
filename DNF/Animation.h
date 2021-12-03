#pragma once
#include "GameObject.h"

class BmpImage;
class Animation : public GameObject
{
public:
	~Animation() = default;

	virtual HRESULT Init(AnimationData data);
	bool UpdateAnimation();
	void Render(HDC hdc, POINTFLOAT pos);
	virtual void Release() override;

	Animation* SetAnimation(AnimationData data);
private:
	BmpImage* mpAnimationImage = nullptr;

	int mCurrFrame = 0;
	int mMaxFrame = 0;
	float mMotionSpeed = 0.0f;
	int mImageFrameSizeX = 0;
	int mImageFrameSizeY = 0;
	int mCorrectionPosX = 0;
	int mCorrectionPosY = 0;
	float mScale = 0.0f;
	bool mbLoop = false;

	float mElapsedTime = 0.0f;
};
