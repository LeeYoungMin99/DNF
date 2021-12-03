#include "stdafx.h"
#include "DemonSlayer.h"
#include "Animation.h"

HRESULT DemonSlayer::Init()
{
	Animation motion;

	mpMotion[DIR::Right][WEAPON_TYPE::Greatsword][STATE::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Greatsword/RightIdle.bmp", 33, 0.1f, 12078, 220, -90, -165, 2.0f, true));
	mpMotion[DIR::Left][WEAPON_TYPE::Greatsword][STATE::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Greatsword/LeftIdle.bmp", 33, 0.1f, 12078, 220, -273, -165, 2.0f, true));
	mpMotion[DIR::Right][WEAPON_TYPE::Greatsword][STATE::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Greatsword/RightWalk.bmp", 10, 0.1f, 3660, 220, -90, -165, 2.0f, true));
	mpMotion[DIR::Left][WEAPON_TYPE::Greatsword][STATE::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Greatsword/LeftWalk.bmp", 10, 0.1f, 3660, 220, -273, -165, 2.0f, true));
	
	mpMotion[DIR::Right][WEAPON_TYPE::Club][STATE::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Club/RightIdle.bmp", 33, 0.1f, 15015, 311, -266, -124, 2.0f, true));
	mpMotion[DIR::Left][WEAPON_TYPE::Club][STATE::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Club/LeftIdle.bmp", 33, 0.1f, 15015, 311, -187, -124, 2.0f, true));
	mpMotion[DIR::Right][WEAPON_TYPE::Club][STATE::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Club/RightWalk.bmp", 10, 0.1f, 4550, 311, -266, -124, 2.0f, true));
	mpMotion[DIR::Left][WEAPON_TYPE::Club][STATE::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Club/LeftWalk.bmp", 10, 0.1f, 4550, 311, -187, -124, 2.0f, true));
	
	mpMotion[DIR::Right][WEAPON_TYPE::Shortsword][STATE::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Shortsword/RightIdle.bmp", 33, 0.1f, 9801, 221, -49, -189, 2.0f, true));
	mpMotion[DIR::Left][WEAPON_TYPE::Shortsword][STATE::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Shortsword/LeftIdle.bmp", 33, 0.1f, 9801, 221, -246, -189, 2.0f, true));
	mpMotion[DIR::Right][WEAPON_TYPE::Shortsword][STATE::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Shortsword/RightWalk.bmp", 10, 0.1f, 2970, 221, -49, -189, 2.0f, true));
	mpMotion[DIR::Left][WEAPON_TYPE::Shortsword][STATE::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Shortsword/LeftWalk.bmp", 10, 0.1f, 2970, 221, -246, -189, 2.0f, true));
	
	mpMotion[DIR::Right][WEAPON_TYPE::Catana][STATE::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Catana/RightIdle.bmp", 33, 0.1f, 10494, 214, -60, -172, 2.0f, true));
	mpMotion[DIR::Left][WEAPON_TYPE::Catana][STATE::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Catana/LeftIdle.bmp", 33, 0.1f, 10494, 214, -255, -172, 2.0f, true));
	mpMotion[DIR::Right][WEAPON_TYPE::Catana][STATE::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Catana/RightWalk.bmp", 10, 0.1f, 3180, 214, -60, -172, 2.0f, true));
	mpMotion[DIR::Left][WEAPON_TYPE::Catana][STATE::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Catana/LeftWalk.bmp", 10, 0.1f, 3180, 214, -255, -172, 2.0f, true));
	
	mpMotion[DIR::Right][WEAPON_TYPE::Snakesword][STATE::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Snakesword/RightIdle.bmp", 33, 0.1f, 13167, 453, -106, -407, 2.0f, true));
	mpMotion[DIR::Left][WEAPON_TYPE::Snakesword][STATE::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Snakesword/LeftIdle.bmp", 33, 0.1f, 13167, 453, -291, -407, 2.0f, true));
	mpMotion[DIR::Right][WEAPON_TYPE::Snakesword][STATE::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Snakesword/RightWalk.bmp", 10, 0.1f, 3990, 453, -106, -407, 2.0f, true));
	mpMotion[DIR::Left][WEAPON_TYPE::Snakesword][STATE::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Snakesword/LeftWalk.bmp", 10, 0.1f, 3990, 453, -291, -407, 2.0f, true));

	{ 45, 115; }
	mDir = eMoveDir::Right;
	mMoveSpeed = 200.0f;
	mPos = { 0,0 };
	return S_OK;
}

void DemonSlayer::Update()
{
	if (MGR_KEY->IsOnceKeyDown('Q'))
	{
		mDir = eMoveDir::Left;
	}
	if (MGR_KEY->IsOnceKeyDown('E'))
	{
		mDir = eMoveDir::Right;
	}
	if (MGR_KEY->IsOnceKeyDown('A'))
	{
		mPos.x -= 1;
	}
	if (MGR_KEY->IsOnceKeyDown('D'))
	{
		mPos.x += 1;
	}
	if (MGR_KEY->IsOnceKeyDown('W'))
	{
		mPos.y -= 1;
	}
	if (MGR_KEY->IsOnceKeyDown('S'))
	{
		mPos.y += 1;
	}


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

	if (false == (MGR_KEY->IsStayKeyDown(VK_LEFT)) && 
		false == (MGR_KEY->IsStayKeyDown(VK_RIGHT)) && 
		false ==(MGR_KEY->IsStayKeyDown(VK_UP)) && 
		false == (MGR_KEY->IsStayKeyDown(VK_DOWN))) 
	{ mState = eDemonSlayerState::Idle; }
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
