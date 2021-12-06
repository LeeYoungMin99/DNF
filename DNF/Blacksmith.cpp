#include "stdafx.h"
#include "Blacksmith.h"
#include "Animation.h"

HRESULT Blacksmith::Init()
{
	mpBlacksmith = MGR_IMAGE->AddImage("Image/Elvengard/Blacksmith/Blacksmith.bmp", IMAGE_SIZE_X, IMAGE_SIZE_Y, true, RGB(255, 0, 255));
	mpBonfire = mpBonfire->SetAnimation(AnimationData("Image/Elvengard/Blacksmith/Bonfire.bmp", 8, 0.1f, 512, 130, 117, 47, 2.0f, true));

	mBodyCollisionRect =
	{ (int)mPos.x + BODY_COLLISION_LEFT + GET_CAMERA_POS.x,
		(int)mPos.y + BODY_COLLISION_TOP + GET_CAMERA_POS.y,
		(int)mPos.x + BODY_COLLISION_RIGHT + GET_CAMERA_POS.x ,
		(int)mPos.y + BODY_COLLISION_BOTTOM + GET_CAMERA_POS.y };

	return S_OK;
}

void Blacksmith::Update()
{
	SetBodyCollisionRect(mPos, { BODY_COLLISION_LEFT,BODY_COLLISION_TOP,BODY_COLLISION_RIGHT,BODY_COLLISION_BOTTOM });
	mpBonfire->UpdateAnimation();
}

void Blacksmith::Render(HDC hdc)
{
	mpBlacksmith->Render(hdc, (int)(mPos.x + GET_CAMERA_POS.x), (int)(mPos.y + CORRECTION_IMAGE_POS_Y + GET_CAMERA_POS.y));
	mpBonfire->Render(hdc, mPos);
}

void Blacksmith::Release()
{
	SAFE_RELEASE(mpBonfire);
}