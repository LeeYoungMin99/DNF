#include "stdafx.h"
#include "SeriaTree.h"

HRESULT SeriaTree::Init()
{
	mpSeriaTree = MGR_IMAGE->AddImage("Image/Elvengard/SeriaTree.bmp", 474 * 2, 395 * 2, true, RGB(255, 0, 255));

	mBodyCollisionRect = { (int)mPos.x - 474 + GET_CAMERA_POS.x,(int)mPos.y - 395 + GET_CAMERA_POS.y,(int)mPos.x + 100 + GET_CAMERA_POS.x  , (int)mPos.y + 395 + GET_CAMERA_POS.y };

	return S_OK;
}

void SeriaTree::Update()
{
	SetBodyCollisionRect(mPos, { -474,-395,100,395 });
}

void SeriaTree::Render(HDC hdc)
{
	mpSeriaTree->Render(hdc, (int)(mPos.x + GET_CAMERA_POS.x), (int)(mPos.y + GET_CAMERA_POS.y));
	Rectangle(hdc, mBodyCollisionRect.left, mBodyCollisionRect.top, mBodyCollisionRect.right, mBodyCollisionRect.bottom);
}

void SeriaTree::Release()
{
}
