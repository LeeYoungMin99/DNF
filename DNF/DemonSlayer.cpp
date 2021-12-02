#include "stdafx.h"
#include "DemonSlayer.h"
#include "Animation.h"

HRESULT DemonSlayer::Init()
{
	SetAnimation(DIR::Right, WEAPON_TYPE::Greatsword, STATE::Idle, AnimationData("Image/CharacterMotion/Greatsword/RightIdle.bmp", 33, 0.1f, 12078, 220, 366, 220, -90, 0, 2.0f, true));
	SetAnimation(DIR::Left, WEAPON_TYPE::Greatsword, STATE::Idle, AnimationData("Image/CharacterMotion/Greatsword/LeftIdle.bmp", 33, 0.1f, 12078, 220, 366, 220, 90, 0, 2.0f, true));
	SetAnimation(DIR::Right, WEAPON_TYPE::Greatsword, STATE::Walk, AnimationData("Image/CharacterMotion/Greatsword/RightWalk.bmp", 10, 0.1f, 3660, 220, 366, 220, -90, 0, 2.0f, true));
	SetAnimation(DIR::Left, WEAPON_TYPE::Greatsword, STATE::Walk, AnimationData("Image/CharacterMotion/Greatsword/LeftWalk.bmp", 10, 0.1f, 3660, 220, 366, 220, 90, 0, 2.0f, true));

	mDir = eMoveDir::Right;
	mMoveSpeed = 200.0f;

	return S_OK;
}

void DemonSlayer::Update()
{
	if (mDir == eMoveDir::Right)
	{
		switch (mState)
		{
		case eDemonSlayerState::Idle:
			UpdateIdleState(DIR::Right);
			break;
		case eDemonSlayerState::Walk:
			UpdateWalkState(DIR::Right);
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
		switch (mState)
		{
		case eDemonSlayerState::Idle:
			UpdateIdleState(DIR::Left);
			break;
		case eDemonSlayerState::Walk:
			UpdateWalkState(DIR::Left);
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
	if (mDir == eMoveDir::Right)
	{
		switch (mState)
		{
		case eDemonSlayerState::Idle:
			RenderState(hdc, DIR::Right, STATE::Idle, mPos);
			break;
		case eDemonSlayerState::Walk:
			RenderState(hdc, DIR::Right, STATE::Walk, mPos);
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
		switch (mState)
		{
		case eDemonSlayerState::Idle:
			RenderState(hdc, DIR::Left, STATE::Idle, mPos);
			break;
		case eDemonSlayerState::Walk:
			RenderState(hdc, DIR::Left, STATE::Walk, mPos);
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
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			for (int k = 0; k < 256; ++k)
			{
				SAFE_RELEASE(mpMotion[i][j][k]);
			}
		}
	}
}

void DemonSlayer::SetAnimation(int dir, int weaponType, int state, AnimationData data)
{
	mpMotion[dir][weaponType][state] = new Animation;
	mpMotion[dir][weaponType][state]->Init(data);
}

void DemonSlayer::UpdateIdleState(int dir)
{
	switch (mWeaponType)
	{
	case DemonSlayer::eWeaponType::Greatsword:
		mpMotion[dir][WEAPON_TYPE::Greatsword][STATE::Idle]->UpdateAnimation();
		break;
	case DemonSlayer::eWeaponType::Club:
		mpMotion[dir][WEAPON_TYPE::Club][STATE::Idle]->UpdateAnimation();
		break;
	case DemonSlayer::eWeaponType::Shortsword:
		mpMotion[dir][WEAPON_TYPE::Shortsword][STATE::Idle]->UpdateAnimation();
		break;
	case DemonSlayer::eWeaponType::Catana:
		mpMotion[dir][WEAPON_TYPE::Catana][STATE::Idle]->UpdateAnimation();
		break;
	case DemonSlayer::eWeaponType::Snakesword:
		mpMotion[dir][WEAPON_TYPE::Snakesword][STATE::Idle]->UpdateAnimation();
		break;
	default:
		break;
	}

	if (MGR_KEY->IsStayKeyDown(VK_LEFT))
	{
		mDir = eMoveDir::Left;
		mState = eDemonSlayerState::Walk;
	}
	else if (MGR_KEY->IsStayKeyDown(VK_RIGHT))
	{
		mDir = eMoveDir::Right;
		mState = eDemonSlayerState::Walk;
	}

	if (MGR_KEY->IsStayKeyDown(VK_UP))
	{
		mState = eDemonSlayerState::Walk;
	}
	else if (MGR_KEY->IsStayKeyDown(VK_DOWN))
	{
		mState = eDemonSlayerState::Walk;
	}
}

void DemonSlayer::UpdateWalkState(int dir)
{
	switch (mWeaponType)
	{
	case DemonSlayer::eWeaponType::Greatsword:
		mpMotion[dir][WEAPON_TYPE::Greatsword][STATE::Walk]->UpdateAnimation();
		break;
	case DemonSlayer::eWeaponType::Club:
		mpMotion[dir][WEAPON_TYPE::Club][STATE::Walk]->UpdateAnimation();
		break;
	case DemonSlayer::eWeaponType::Shortsword:
		mpMotion[dir][WEAPON_TYPE::Shortsword][STATE::Walk]->UpdateAnimation();
		break;
	case DemonSlayer::eWeaponType::Catana:
		mpMotion[dir][WEAPON_TYPE::Catana][STATE::Walk]->UpdateAnimation();
		break;
	case DemonSlayer::eWeaponType::Snakesword:
		mpMotion[dir][WEAPON_TYPE::Snakesword][STATE::Walk]->UpdateAnimation();
		break;
	default:
		break;
	}

	if (MGR_KEY->IsStayKeyDown(VK_LEFT))
	{
		mDir = eMoveDir::Left;
		mPos.x -= DELTA_TIME * mMoveSpeed;
	}
	else if (MGR_KEY->IsStayKeyDown(VK_RIGHT))
	{
		mDir = eMoveDir::Right;
		mPos.x += DELTA_TIME * mMoveSpeed;
	}

	if (MGR_KEY->IsStayKeyDown(VK_UP)) { mPos.y -= DELTA_TIME * mMoveSpeed; }
	else if (MGR_KEY->IsStayKeyDown(VK_DOWN)) { mPos.y += DELTA_TIME * mMoveSpeed; }

	if (MGR_KEY->IsOnceKeyUp(VK_LEFT) && !(MGR_KEY->IsStayKeyDown(VK_RIGHT)) && !(MGR_KEY->IsStayKeyDown(VK_UP)) && !(MGR_KEY->IsStayKeyDown(VK_DOWN))) { mState = eDemonSlayerState::Idle; }
	if (MGR_KEY->IsOnceKeyUp(VK_RIGHT) && !(MGR_KEY->IsStayKeyDown(VK_LEFT)) && !(MGR_KEY->IsStayKeyDown(VK_UP)) && !(MGR_KEY->IsStayKeyDown(VK_DOWN))) { mState = eDemonSlayerState::Idle; }
	if (MGR_KEY->IsOnceKeyUp(VK_UP) && !(MGR_KEY->IsStayKeyDown(VK_LEFT)) && !(MGR_KEY->IsStayKeyDown(VK_RIGHT)) && !(MGR_KEY->IsStayKeyDown(VK_DOWN))) { mState = eDemonSlayerState::Idle; }
	if (MGR_KEY->IsOnceKeyUp(VK_DOWN) && !(MGR_KEY->IsStayKeyDown(VK_LEFT)) && !(MGR_KEY->IsStayKeyDown(VK_RIGHT)) && !(MGR_KEY->IsStayKeyDown(VK_UP))) { mState = eDemonSlayerState::Idle; }
}

void DemonSlayer::RenderState(HDC hdc, int dir, int state, POINTFLOAT pos)
{
	switch (mWeaponType)
	{
	case DemonSlayer::eWeaponType::Greatsword:
		mpMotion[dir][WEAPON_TYPE::Greatsword][state]->Render(hdc, pos);
		break;
	case DemonSlayer::eWeaponType::Club:
		mpMotion[dir][WEAPON_TYPE::Club][state]->Render(hdc, pos);
		break;
	case DemonSlayer::eWeaponType::Shortsword:
		mpMotion[dir][WEAPON_TYPE::Shortsword][state]->Render(hdc, pos);
		break;
	case DemonSlayer::eWeaponType::Catana:
		mpMotion[dir][WEAPON_TYPE::Catana][state]->Render(hdc, pos);
		break;
	case DemonSlayer::eWeaponType::Snakesword:
		mpMotion[dir][WEAPON_TYPE::Snakesword][state]->Render(hdc, pos);
		break;
	default:
		break;
	}
}
