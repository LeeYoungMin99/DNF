#include "stdafx.h"
#include "Seria.h"
#include "Animation.h"

HRESULT Seria::Init()
{
	mpIdleMotion = mpIdleMotion->SetAnimation(AnimationData("Image/CharacterMotion/NonPlayableCharacter/Seria/Idle.bmp", 12, 0.2f, 684, 118, -(BODY_SIZE_X / 2), -(BODY_SIZE_Y / 2), 2.0f, true));
	mpHoverMotion = mpHoverMotion->SetAnimation(AnimationData("Image/CharacterMotion/NonPlayableCharacter/Seria/Hover.bmp", 12, 0.2f, 684, 118, -(BODY_SIZE_X / 2), -(BODY_SIZE_Y / 2), 2.0f, true));

	const float posX = (float)WIN_SIZE_X_HALF;
	const float posY = (float)(WIN_SIZE_Y_HALF - (BODY_SIZE_Y / 2));

	mPos = { posX, posY };
	return S_OK;
}

void Seria::Update()
{
	const RECT COLLISION_RECT = { LONG(mPos.x - BODY_SIZE_X),LONG(mPos.y - BODY_SIZE_Y),LONG(mPos.x + BODY_SIZE_X),LONG(mPos.y + BODY_SIZE_Y) };

	mpIdleMotion->UpdateAnimation();
	mpHoverMotion->UpdateAnimation();

	switch (mState)
	{
	case Seria::eSeriaState::Idle:
		if (PtInRect(&COLLISION_RECT, g_ptMouse))
		{
			mState = eSeriaState::Hover;
		}
		break;
	case Seria::eSeriaState::Hover:
		if (false == PtInRect(&COLLISION_RECT, g_ptMouse))
		{
			mState = eSeriaState::Idle;
		}

		if (MGR_KEY->IsOnceKeyDown(VK_LBUTTON))
		{
			cout << "버튼들 나와야 함" << endl;
		}
		break;
	}
}

void Seria::Render(HDC hdc)
{
	switch (mState)
	{
	case Seria::eSeriaState::Idle:
		mpIdleMotion->Render(hdc, mPos);
		break;
	case Seria::eSeriaState::Hover:
		mpHoverMotion->Render(hdc, mPos);
		break;
	}
}

void Seria::Release()
{
	SAFE_RELEASE(mpIdleMotion);
	SAFE_RELEASE(mpHoverMotion);
}
