#pragma once
#include "MapObject.h"

class BmpImage;
class SeriaTree : public MapObject
{
public:
	virtual ~SeriaTree() = default;;

	virtual HRESULT Init();
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	BmpImage* mpSeriaTree = nullptr;

	const int IMAGE_SIZE_X = 948;
	const int IMAGE_SIZE_Y = 790;
	const int CORRECTION_IMAGE_POS_Y = -200;
	const int BODY_COLLISION_LEFT = -474;
	const int BODY_COLLISION_TOP = -200;
	const int BODY_COLLISION_RIGHT = 100;
	const int BODY_COLLISION_BOTTOM = 200;
};