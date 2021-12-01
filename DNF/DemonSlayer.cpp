#include "stdafx.h"
#include "DemonSlayer.h"
#include "Animation.h"

HRESULT DemonSlayer::Init()
{
	greatswordRightIdleMotion = new Animation;
	greatswordRightIdleMotion->Init(AnimationData("Image/CharacterMotion/Greatsword/RightIdle.bmp", 33, 0.1f, 12078, 220, 366, 220, -90, 0, 2.0f, true));
	greatswordLeftIdleMotion = new Animation;
	greatswordLeftIdleMotion->Init(AnimationData("Image/CharacterMotion/Greatsword/LeftIdle.bmp", 33, 0.1f, 12078, 220, 366, 220, 90, 0, 2.0f, true));
	greatswordRightWalkMotion = new Animation;
	greatswordRightWalkMotion->Init(AnimationData("Image/CharacterMotion/Greatsword/RightWalk.bmp", 10, 0.1f, 3660, 220, 366, 220, -90, 0, 2.0f, true));
	greatswordLeftWalkMotion = new Animation;
	greatswordLeftWalkMotion->Init(AnimationData("Image/CharacterMotion/Greatsword/LeftWalk.bmp", 10, 0.1f, 3660, 220, 366, 220, 90, 0, 2.0f, true));

	dir = eMoveDir::Right;
	moveSpeed = 200.0f;

	return S_OK;
}

void DemonSlayer::Update()
{
	if (MGR_KEY->IsStayKeyDown(VK_LEFT))
	{
		dir = eMoveDir::Left;
		state = eDemonSlayerState::greatswordWalk;
		pos.x -= DELTA_TIME * moveSpeed;
	}
	else if (MGR_KEY->IsStayKeyDown(VK_RIGHT))
	{
		dir = eMoveDir::Right;
		state = eDemonSlayerState::greatswordWalk;
		pos.x += DELTA_TIME * moveSpeed;
	}

	if (MGR_KEY->IsOnceKeyUp(VK_LEFT)) { state = eDemonSlayerState::greatswordIdle; }
	else if (MGR_KEY->IsOnceKeyUp(VK_RIGHT)) { state = eDemonSlayerState::greatswordIdle; }

	if (dir == eMoveDir::Right)
	{
		switch (state)
		{
		case eDemonSlayerState::greatswordIdle:
			greatswordRightIdleMotion->UpdateAnimation();
			break;
		case eDemonSlayerState::greatswordWalk:
			greatswordRightWalkMotion->UpdateAnimation();
			break;
		case eDemonSlayerState::Run:
			break;
		case eDemonSlayerState::Damage:
			break;
		case eDemonSlayerState::Jump:
			break;
		case eDemonSlayerState::BasickAttak1:
			break;
		case eDemonSlayerState::BasickAttak2:
			break;
		case eDemonSlayerState::BasickAttak3:
			break;
		case eDemonSlayerState::BasickAttak4:
			break;
		default:
			break;
		}
	}
	else
	{
		switch (state)
		{
		case eDemonSlayerState::greatswordIdle:
			greatswordLeftIdleMotion->UpdateAnimation();
			break;
		case eDemonSlayerState::greatswordWalk:
			greatswordLeftWalkMotion->UpdateAnimation();
			break;
		case eDemonSlayerState::Run:
			break;
		case eDemonSlayerState::Damage:
			break;
		case eDemonSlayerState::Jump:
			break;
		case eDemonSlayerState::BasickAttak1:
			break;
		case eDemonSlayerState::BasickAttak2:
			break;
		case eDemonSlayerState::BasickAttak3:
			break;
		case eDemonSlayerState::BasickAttak4:
			break;
		default:
			break;
		}
	}
}

void DemonSlayer::Render(HDC hdc)
{
	if (dir == eMoveDir::Right)
	{
		switch (state)
		{
		case eDemonSlayerState::greatswordIdle:
			greatswordRightIdleMotion->Render(hdc, pos);
			break;
		case eDemonSlayerState::greatswordWalk:
			greatswordRightWalkMotion->Render(hdc, pos);
			break;
		case eDemonSlayerState::Run:
			break;
		case eDemonSlayerState::Damage:
			break;
		case eDemonSlayerState::Jump:
			break;
		case eDemonSlayerState::BasickAttak1:
			break;
		case eDemonSlayerState::BasickAttak2:
			break;
		case eDemonSlayerState::BasickAttak3:
			break;
		case eDemonSlayerState::BasickAttak4:
			break;
		default:
			break;
		}
	}
	else
	{
		switch (state)
		{
		case eDemonSlayerState::greatswordIdle:
			greatswordLeftIdleMotion->Render(hdc, pos);
			break;
		case eDemonSlayerState::greatswordWalk:
			greatswordLeftWalkMotion->Render(hdc, pos);
			break;
		case eDemonSlayerState::Run:
			break;
		case eDemonSlayerState::Damage:
			break;
		case eDemonSlayerState::Jump:
			break;
		case eDemonSlayerState::BasickAttak1:
			break;
		case eDemonSlayerState::BasickAttak2:
			break;
		case eDemonSlayerState::BasickAttak3:
			break;
		case eDemonSlayerState::BasickAttak4:
			break;
		default:
			break;
		}
	}
}

void DemonSlayer::Release()
{
	SAFE_RELEASE(greatswordRightIdleMotion);
	SAFE_RELEASE(greatswordLeftIdleMotion);
	SAFE_RELEASE(greatswordRightWalkMotion);
	SAFE_RELEASE(greatswordLeftWalkMotion);
	SAFE_RELEASE(clubRightIdleMotion);
	SAFE_RELEASE(clubLeftIdleMotion);
}
