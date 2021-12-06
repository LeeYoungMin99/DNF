#pragma once
#include "MapObject.h"

class BmpImage;
class SmarmyTree : public MapObject
{
public:
	~SmarmyTree() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	BmpImage* mpSmarmyTree = nullptr;

	const int IMAGE_SIZE_X = 392;
	const int IMAGE_SIZE_Y = 770;
	const int CORRECTION_IMAGE_POS_Y = -300;
	const int BODY_COLLISION_LEFT = -IMAGE_SIZE_X / 2 - 200;
	const int BODY_COLLISION_TOP = IMAGE_SIZE_Y / 2 - 400;
	const int BODY_COLLISION_RIGHT = IMAGE_SIZE_X / 2;
	const int BODY_COLLISION_BOTTOM = IMAGE_SIZE_Y / 2 - 170;
};
