#include "stdafx.h"
#include "SeriaTree.h"

HRESULT SeriaTree::Init()
{
	mpSeriaTree = MGR_IMAGE->AddImage("Image/Elvengard/SeriaTree.bmp", IMAGE_SIZE_X, IMAGE_SIZE_Y, true, RGB(255, 0, 255));

	mBodyCollisionRect =
	{ (int)mPos.x + BODY_COLLISION_LEFT + GET_CAMERA_POS.x,
		(int)mPos.y + BODY_COLLISION_TOP + GET_CAMERA_POS.y,
		(int)mPos.x + BODY_COLLISION_RIGHT + GET_CAMERA_POS.x ,
		(int)mPos.y + BODY_COLLISION_BOTTOM + GET_CAMERA_POS.y };

	return S_OK;
}

void SeriaTree::Update()
{
	SetBodyCollisionRect(mPos, { BODY_COLLISION_LEFT,BODY_COLLISION_TOP,BODY_COLLISION_RIGHT,BODY_COLLISION_BOTTOM });
}

void SeriaTree::Render(HDC hdc)
{
	mpSeriaTree->Render(hdc, (int)(mPos.x + GET_CAMERA_POS.x), (int)(mPos.y + CORRECTION_IMAGE_POS_Y + GET_CAMERA_POS.y));
}

void SeriaTree::Release()
{
}
