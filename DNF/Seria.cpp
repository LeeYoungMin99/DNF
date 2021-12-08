#include "stdafx.h"
#include "Seria.h"
#include "Animation.h"

HRESULT Seria::Init()
{
	mpIdleMotion = mpIdleMotion->SetAnimation(AnimationData("Image/CharacterMotion/NonPlayableCharacter/Seria/Idle.bmp", 12, 0.2f, 684, 118, -(BODY_SIZE_X / 2), -(BODY_SIZE_Y / 2), 2.0f, true));
	mpHoverMotion = mpHoverMotion->SetAnimation(AnimationData("Image/CharacterMotion/NonPlayableCharacter/Seria/Hover.bmp", 12, 0.2f, 684, 118, -(BODY_SIZE_X / 2), -(BODY_SIZE_Y / 2), 2.0f, true));

	return S_OK;
}

void Seria::Update()
{
	mpIdleMotion->UpdateAnimation();
	mpHoverMotion->UpdateAnimation();

	SetBodyCollisionRect(mPos, { BODY_COLLISION_LEFT,BODY_COLLISION_TOP,BODY_COLLISION_RIGHT,BODY_COLLISION_BOTTOM });

	if (mState == Seria::eSeriaState::Idle) { if (PtInRect(&mBodyCollisionRect, Input::GetMousePosition())) { mState = eSeriaState::Hover; } }
	else if (mState == Seria::eSeriaState::Hover) { if (false == PtInRect(&mBodyCollisionRect, Input::GetMousePosition())) { mState = eSeriaState::Idle; } }
}

void Seria::Render(HDC hdc)
{
	if (mState == Seria::eSeriaState::Idle) { mpIdleMotion->Render(hdc, mPos); }
	else if (mState == Seria::eSeriaState::Hover) { mpHoverMotion->Render(hdc, mPos); }
}

void Seria::Release()
{
	SAFE_RELEASE(mpIdleMotion);
	SAFE_RELEASE(mpHoverMotion);
}
