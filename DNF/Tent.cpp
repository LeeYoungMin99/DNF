#include "stdafx.h"
#include "Tent.h"

HRESULT Tent::Init()
{
	mpTent = MGR_IMAGE->AddImage("Image/Elvengard/Tent.bmp", IMAGE_SIZE_X, IMAGE_SIZE_Y, true, RGB(255, 0, 255));

	mBodyCollisionRect =
	{ (int)mPos.x + BODY_COLLISION_LEFT + GET_CAMERA_POS.x,
		(int)mPos.y + BODY_COLLISION_TOP + GET_CAMERA_POS.y,
		(int)mPos.x + BODY_COLLISION_RIGHT + GET_CAMERA_POS.x ,
		(int)mPos.y + BODY_COLLISION_BOTTOM + GET_CAMERA_POS.y };

	return S_OK;
}

void Tent::Update()
{
	SetBodyCollisionRect(mPos, { BODY_COLLISION_LEFT,BODY_COLLISION_TOP,BODY_COLLISION_RIGHT,BODY_COLLISION_BOTTOM });
}

void Tent::Render(HDC hdc)
{
	mpTent->Render(hdc, (int)(mPos.x + GET_CAMERA_POS.x), (int)(mPos.y + CORRECTION_IMAGE_POS_Y + GET_CAMERA_POS.y));
}

void Tent::Release()
{
}
