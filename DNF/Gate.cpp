#include "stdafx.h"
#include "Gate.h"
#include "Animation.h"
#include "CollisionManager.h"
#include "Scene.h"

HRESULT Gate::Init()
{
	mpGate = mpGate->SetAnimation(AnimationData("Image/Elvengard/Gate.bmp", 29, 0.1f, 3103, 39, 0, 0, 2.0f, true));

	mBodyCollisionRect =
	{ (int)mPos.x + BODY_COLLISION_LEFT + GET_CAMERA_POS.x,
		(int)mPos.y + BODY_COLLISION_TOP + GET_CAMERA_POS.y,
		(int)mPos.x + BODY_COLLISION_RIGHT + GET_CAMERA_POS.x ,
		(int)mPos.y + BODY_COLLISION_BOTTOM + GET_CAMERA_POS.y };

	return S_OK;
}

void Gate::Update()
{
	SetBodyCollisionRect(mPos, { BODY_COLLISION_LEFT,BODY_COLLISION_TOP,BODY_COLLISION_RIGHT,BODY_COLLISION_BOTTOM });
	mpGate->UpdateAnimation();
}

void Gate::Render(HDC hdc)
{
	Rectangle(hdc, mBodyCollisionRect.left, mBodyCollisionRect.top, mBodyCollisionRect.right, mBodyCollisionRect.bottom);
	mpGate->Render(hdc, { mPos.x , mPos.y });
}

void Gate::Release()
{
	SAFE_RELEASE(mpGate);
}

void Gate::OnCollidedBody(RECT intersectionRect)
{
	mpCurrScene->SetAreaTag(mConnectedArea);
	mpCollisionManager->SetNextAreaTag(mConnectedArea);
}
