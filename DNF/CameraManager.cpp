#include "stdafx.h"
#include "CameraManager.h"
#include "Player.h"
#include "PositionComponent.h"

void CameraManager::Update()
{
	LONG playerScreenPosX = _player->GetX() + _pos.x;
	LONG playerScreenPosY = _player->GetY() + _pos.y;

	if (playerScreenPosX <= 433)
	{
		AddX(433 - playerScreenPosX);
	}
	else if (playerScreenPosX >= 633)
	{
		AddX(633 - playerScreenPosX);
	}

	if (playerScreenPosY <= 200)
	{
		AddY(200 - playerScreenPosY);
	}
	else if (playerScreenPosY >= 400)
	{
		AddY(400 - playerScreenPosY);
	}
}

void CameraManager::SetCameraPos(const LONG& posX, const LONG& posY)
{
	_pos.x = posX;
	_pos.y = posY;
}

void CameraManager::AddX(const LONG& x)
{
	LONG temp = _pos.x + x;
	if (temp > _maxPos.x)
	{
		_pos.x = _maxPos.x;
	}
	else if (temp < _minPos.x)
	{
		_pos.x = _minPos.x;
	}
	else
	{
		_pos.x = temp;
	}
}

void CameraManager::AddY(const LONG& y)
{
	LONG temp = _pos.y + y;
	if (temp > _maxPos.y)
	{
		_pos.y = _maxPos.y;
	}
	else if (temp < _minPos.y)
	{
		_pos.y = _minPos.y;
	}
	else
	{
		_pos.y = temp;
	}
}

void CameraManager::SetCameraMaxPos(const LONG& maxX, const LONG& maxY)
{
	_maxPos.x = maxX;
	_maxPos.y = maxY;
}

void CameraManager::SetCameraMinPos(const LONG& minX, const LONG& minY)
{
	_minPos.x = minX;
	_minPos.y = minY;
}