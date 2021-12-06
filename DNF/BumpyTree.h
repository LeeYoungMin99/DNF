#pragma once
#include "MapObject.h"

class BmpImage;
class BumpyTree : public MapObject
{
public:
	~BumpyTree() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	BmpImage* mpBumpyTree = nullptr;

	const int IMAGE_SIZE_X = 532;
	const int IMAGE_SIZE_Y = 762;
	const int CORRECTION_IMAGE_POS_Y = -300;
	const int BODY_COLLISION_LEFT = -IMAGE_SIZE_X / 2;
	const int BODY_COLLISION_TOP = IMAGE_SIZE_Y / 2 - 400;
	const int BODY_COLLISION_RIGHT = IMAGE_SIZE_X / 2;
	const int BODY_COLLISION_BOTTOM = IMAGE_SIZE_Y / 2 - 170;
};
