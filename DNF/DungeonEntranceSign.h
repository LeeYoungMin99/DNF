#pragma once
#include "MapObject.h"

class BmpImage;
class DungeonEntranceSign : public MapObject
{
public:
	~DungeonEntranceSign() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	BmpImage* mpDungeonEntranceSign = nullptr;

	const int IMAGE_SIZE_X = 196;
	const int IMAGE_SIZE_Y = 388;
	const int CORRECTION_IMAGE_POS_Y = -144;
	const int BODY_COLLISION_LEFT = -IMAGE_SIZE_X / 2;
	const int BODY_COLLISION_TOP = IMAGE_SIZE_Y / 2- 244 ;
	const int BODY_COLLISION_RIGHT = IMAGE_SIZE_X / 2;
	const int BODY_COLLISION_BOTTOM = IMAGE_SIZE_Y / 2 - 144 ;
};

