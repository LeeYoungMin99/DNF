#include "stdafx.h"
#include "CameraManager.h"

LONG CameraManager::GetX()
{
	return mPos.x;
}

LONG CameraManager::GetY()
{
	return mPos.y;
}

void CameraManager::SetCameraPos(LONG posX, LONG posY)
{
	mPos.x = posX;
	mPos.y = posY;
}

void CameraManager::AddX(LONG x)
{
	LONG temp = mPos.x + x;
	if (temp > mMaxPos.x)
	{
		mPos.x = mMaxPos.x;
	}
	else if (temp < mMinPos.x)
	{
		mPos.x = mMinPos.x;
	}
	else
	{
		mPos.x = temp;
	}
}

void CameraManager::AddY(LONG y)
{
	LONG temp = mPos.y + y;
	if (temp > mMaxPos.y)
	{
		mPos.y = mMaxPos.y;
	}
	else if (temp < mMinPos.y)
	{
		mPos.y = mMinPos.y;
	}
	else
	{
		mPos.y = temp;
	}
}

void CameraManager::SetCameraMaxPos(LONG maxX, LONG maxY)
{
	mMaxPos.x = maxX;
	mMaxPos.y = maxY;
}

void CameraManager::SetCameraMinPos(LONG minX, LONG minY)
{
	mMinPos.x = minX;
	mMinPos.y = minY;
}

void CameraManager::Init()
{
}

void CameraManager::Update()
{
}

void CameraManager::Render()
{
}

void CameraManager::Release()
{
}
