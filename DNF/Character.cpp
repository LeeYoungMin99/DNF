#include "stdafx.h"
#include "Character.h"

Character::eDirX Character::GetDirX() const noexcept
{
	return mDirX;
}

Character::eDirY Character::GetDirY() const noexcept
{
	return mDirY;
}

int Character::GetMoveSpeed() const noexcept
{
	return mMoveSpeed;
}

Character::eState Character::GetState() const noexcept
{
	return mState;
}

int Character::GetZ() const noexcept
{
	return mPosZ;
}

float Character::GetAcceleration() const noexcept
{
	return mAcceleration;
}

float Character::GetResistance() const noexcept
{
	return mResistance;
}

void Character::AddZ(int z) noexcept
{
	mPosZ += z;
}

void Character::SetDirX(eDirX dir) noexcept
{
	mDirX = dir;
}

void Character::SetDirY(eDirY dir) noexcept
{
	mDirY = dir;
}

void Character::SetMoveSpeed(int speed) noexcept
{
	mMoveSpeed = speed;
}

void Character::SetState(eState state) noexcept
{
	mState = state;
}

void Character::SetZ(int z) noexcept
{
	mPosZ = z;
}

void Character::SetAcceleration(float accel) noexcept
{
	mAcceleration = accel;
}

void Character::SetResistance(float resist) noexcept
{
	mResistance = resist;
}
