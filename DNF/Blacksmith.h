#pragma once
#include "MapObject.h"

class Animation;
class BmpImage;
class Blacksmith : public MapObject
{
public:
	~Blacksmith() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	BmpImage* mpBlacksmith = nullptr;
	Animation* mpBonfire = nullptr;

	const int IMAGE_SIZE_X = 1422;
	const int IMAGE_SIZE_Y = 716;
	const int CORRECTION_IMAGE_POS_Y = 0;
	const int BODY_COLLISION_LEFT = -400;
	const int BODY_COLLISION_TOP = IMAGE_SIZE_Y / 2 - 400;
	const int BODY_COLLISION_RIGHT = IMAGE_SIZE_X / 2;
	const int BODY_COLLISION_BOTTOM = IMAGE_SIZE_Y / 2 +42;
};
