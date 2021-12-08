#include "stdafx.h"
#include "DemonSlayer.h"
#include "Animation.h"

HRESULT DemonSlayer::Init()
{
	Animation motion;

	mpMotion[(int)eMoveDir::Right][(int)DemonSlayer::eWeaponType::Greatsword][(int)DemonSlayer::eDemonSlayerState::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Greatsword/RightIdle.bmp", 33, 0.1f, 12078, 220, -93, -270, 2.0f, true));
	mpMotion[(int)eMoveDir::Left][(int)DemonSlayer::eWeaponType::Greatsword][(int)DemonSlayer::eDemonSlayerState::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Greatsword/LeftIdle.bmp", 33, 0.1f, 12078, 220, -273, -270, 2.0f, true));
	mpMotion[(int)eMoveDir::Right][(int)DemonSlayer::eWeaponType::Greatsword][(int)DemonSlayer::eDemonSlayerState::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Greatsword/RightWalk.bmp", 10, 0.1f, 3660, 220, -93, -270, 2.0f, true));
	mpMotion[(int)eMoveDir::Left][(int)DemonSlayer::eWeaponType::Greatsword][(int)DemonSlayer::eDemonSlayerState::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Greatsword/LeftWalk.bmp", 10, 0.1f, 3660, 220, -273, -270, 2.0f, true));

	mpMotion[(int)eMoveDir::Right][(int)DemonSlayer::eWeaponType::Club][(int)DemonSlayer::eDemonSlayerState::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Club/RightIdle.bmp", 33, 0.1f, 15015, 311, -269, -229, 2.0f, true));
	mpMotion[(int)eMoveDir::Left][(int)DemonSlayer::eWeaponType::Club][(int)DemonSlayer::eDemonSlayerState::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Club/LeftIdle.bmp", 33, 0.1f, 15015, 311, -188, -229, 2.0f, true));
	mpMotion[(int)eMoveDir::Right][(int)DemonSlayer::eWeaponType::Club][(int)DemonSlayer::eDemonSlayerState::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Club/RightWalk.bmp", 10, 0.1f, 4550, 311, -269, -229, 2.0f, true));
	mpMotion[(int)eMoveDir::Left][(int)DemonSlayer::eWeaponType::Club][(int)DemonSlayer::eDemonSlayerState::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Club/LeftWalk.bmp", 10, 0.1f, 4550, 311, -188, -229, 2.0f, true));

	mpMotion[(int)eMoveDir::Right][(int)DemonSlayer::eWeaponType::Shortsword][(int)DemonSlayer::eDemonSlayerState::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Shortsword/RightIdle.bmp", 33, 0.1f, 9801, 221, -52, -294, 2.0f, true));
	mpMotion[(int)eMoveDir::Left][(int)DemonSlayer::eWeaponType::Shortsword][(int)DemonSlayer::eDemonSlayerState::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Shortsword/LeftIdle.bmp", 33, 0.1f, 9801, 221, -247, -294, 2.0f, true));
	mpMotion[(int)eMoveDir::Right][(int)DemonSlayer::eWeaponType::Shortsword][(int)DemonSlayer::eDemonSlayerState::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Shortsword/RightWalk.bmp", 10, 0.1f, 2970, 221, -52, -294, 2.0f, true));
	mpMotion[(int)eMoveDir::Left][(int)DemonSlayer::eWeaponType::Shortsword][(int)DemonSlayer::eDemonSlayerState::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Shortsword/LeftWalk.bmp", 10, 0.1f, 2970, 221, -247, -294, 2.0f, true));

	mpMotion[(int)eMoveDir::Right][(int)DemonSlayer::eWeaponType::Catana][(int)DemonSlayer::eDemonSlayerState::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Catana/RightIdle.bmp", 33, 0.1f, 10494, 214, -63, -277, 2.0f, true));
	mpMotion[(int)eMoveDir::Left][(int)DemonSlayer::eWeaponType::Catana][(int)DemonSlayer::eDemonSlayerState::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Catana/LeftIdle.bmp", 33, 0.1f, 10494, 214, -256, -277, 2.0f, true));
	mpMotion[(int)eMoveDir::Right][(int)DemonSlayer::eWeaponType::Catana][(int)DemonSlayer::eDemonSlayerState::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Catana/RightWalk.bmp", 10, 0.1f, 3180, 214, -63, -277, 2.0f, true));
	mpMotion[(int)eMoveDir::Left][(int)DemonSlayer::eWeaponType::Catana][(int)DemonSlayer::eDemonSlayerState::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Catana/LeftWalk.bmp", 10, 0.1f, 3180, 214, -256, -277, 2.0f, true));

	mpMotion[(int)eMoveDir::Right][(int)DemonSlayer::eWeaponType::Snakesword][(int)DemonSlayer::eDemonSlayerState::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Snakesword/RightIdle.bmp", 33, 0.1f, 13167, 453, -109, -512, 2.0f, true));
	mpMotion[(int)eMoveDir::Left][(int)DemonSlayer::eWeaponType::Snakesword][(int)DemonSlayer::eDemonSlayerState::Idle] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Snakesword/LeftIdle.bmp", 33, 0.1f, 13167, 453, -292, -512, 2.0f, true));
	mpMotion[(int)eMoveDir::Right][(int)DemonSlayer::eWeaponType::Snakesword][(int)DemonSlayer::eDemonSlayerState::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Snakesword/RightWalk.bmp", 10, 0.1f, 3990, 453, -109, -512, 2.0f, true));
	mpMotion[(int)eMoveDir::Left][(int)DemonSlayer::eWeaponType::Snakesword][(int)DemonSlayer::eDemonSlayerState::Walk] = motion.SetAnimation(AnimationData("Image/CharacterMotion/PlayableCharacter/Snakesword/LeftWalk.bmp", 10, 0.1f, 3990, 453, -292, -512, 2.0f, true));

	SetBodyCollisionRect(mPos, { -36,0,36,0 });

	{ 45, 115; }
	mDir = eMoveDir::Right;
	mMoveSpeed = 1000.0f;
	mPos = { 0,0 };
	mObjectType = eObjectType::Character;
	return S_OK;
}

void DemonSlayer::Update()
{
	if (Input::GetButtonDown('Q')) { mDir = eMoveDir::Left; }
	if (Input::GetButtonDown('E')) { mDir = eMoveDir::Right; }
	if (Input::GetButtonDown('A')) { mPos.x -= 1; }
	if (Input::GetButtonDown('D')) { mPos.x += 1; }
	if (Input::GetButtonDown('W')) { mPos.y -= 1; }
	if (Input::GetButtonDown('S')) { mPos.y += 1; }

	if (mState == eDemonSlayerState::Idle) { UpdateIdle(); }
	else if (mState == eDemonSlayerState::Walk) { UpdateWalk(); }

	mpMotion[(int)mDir][(int)mWeaponType][(int)mState]->UpdateAnimation();
	SetBodyCollisionRect(mPos, { -40,-20,40,20 });
}

void DemonSlayer::Render(HDC hdc)
{
	Rectangle(hdc, mBodyCollisionRect.left, mBodyCollisionRect.top, mBodyCollisionRect.right, mBodyCollisionRect.bottom);
	mpMotion[(int)mDir][(int)mWeaponType][(int)mState]->Render(hdc, mPos);
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

void DemonSlayer::UpdateIdle()
{
	if (Input::GetButton(VK_LEFT))
	{
		mpMotion[(int)mDir][(int)mWeaponType][(int)mState]->InitFrame();
		mState = eDemonSlayerState::Walk;
		mDir = eMoveDir::Left;
	}
	else if (Input::GetButton(VK_RIGHT))
	{
		mpMotion[(int)mDir][(int)mWeaponType][(int)mState]->InitFrame();
		mState = eDemonSlayerState::Walk;
		mDir = eMoveDir::Right;
	}

	if (Input::GetButton(VK_UP)) { mState = eDemonSlayerState::Walk; }
	else if (Input::GetButton(VK_DOWN)) { mState = eDemonSlayerState::Walk; }
}

void DemonSlayer::UpdateWalk()
{
	if (Input::GetButton(VK_LEFT))
	{
		mDir = eMoveDir::Left;
		mPos.x -= DELTA_TIME * mMoveSpeed;
	}
	else if (Input::GetButton(VK_RIGHT))
	{
		mDir = eMoveDir::Right;
		mPos.x += DELTA_TIME * mMoveSpeed;
	}

	if (Input::GetButton(VK_UP)) { mPos.y -= DELTA_TIME * mMoveSpeed; }
	else if (Input::GetButton(VK_DOWN)) { mPos.y += DELTA_TIME * mMoveSpeed; }

	if (false == (Input::GetButton(VK_LEFT)) &&
		false == (Input::GetButton(VK_RIGHT)) &&
		false == (Input::GetButton(VK_UP)) &&
		false == (Input::GetButton(VK_DOWN)))
	{
		mpMotion[(int)mDir][(int)mWeaponType][(int)mState]->InitFrame();
		mState = eDemonSlayerState::Idle;
	}
}

void DemonSlayer::OnCollidedBody(RECT intersectionRect)
{
	int width = intersectionRect.right - intersectionRect.left;
	int height = intersectionRect.bottom - intersectionRect.top;

	if (width > height)
	{
		if (intersectionRect.bottom == mBodyCollisionRect.bottom) { mPos.y -= height; }
		else { mPos.y += height; }
	}
	else
	{
		if (intersectionRect.left == mBodyCollisionRect.left) { mPos.x += width; }
		else { mPos.x -= width; }
	}

	SetBodyCollisionRect(mPos, { -40,-20,40,20 });
}

void DemonSlayer::OnCollidedAttack(eAttackType attackType, eAttackElementType elementType, int damage)
{
}
