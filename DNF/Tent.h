#pragma once
#include "MapObject.h"

class BmpImage;
class Tent : public MapObject
{
public:
	~Tent() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	BmpImage* mpTent = nullptr;

	const int IMAGE_SIZE_X = 582;
	const int IMAGE_SIZE_Y = 316;
	const int CORRECTION_IMAGE_POS_Y = -100;
	const int BODY_COLLISION_LEFT = -IMAGE_SIZE_X / 2;
	const int BODY_COLLISION_TOP = IMAGE_SIZE_Y / 2 - 200;
	const int BODY_COLLISION_RIGHT = IMAGE_SIZE_X / 2;
	const int BODY_COLLISION_BOTTOM = IMAGE_SIZE_Y / 2 - 100;
};
