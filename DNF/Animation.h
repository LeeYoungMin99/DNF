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
private:
	BmpImage* animationImage = nullptr;

	int currFrame = 0;
	int maxFrame = 0;
	float motionSpeed = 0.0f;
	int imageFrameSizeX = 0;
	int imageFrameSizeY = 0;
	int correctionPosX = 0;
	int correctionPosY = 0;
	float scale = 0.0f;
	bool loop = false;
	bool isFlip = false;

	float elapsedTime = 0.0f;
};
