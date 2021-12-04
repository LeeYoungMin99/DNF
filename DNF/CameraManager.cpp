#include "stdafx.h"
#include "CameraManager.h"

POINT CameraManager::GetCameraPos()
{
	return pos;
}

void CameraManager::SetCameraPos(int posX, int posY)
{
	pos.x = posX;
	pos.y = posY;
}

void CameraManager::AddCameraPos(int posX, int posY)
{
	POINT temp = { pos.x + posX, pos.y + posY };
	if (temp.x > maxPos.x || temp.x < minPos.x ||
		temp.y > maxPos.y || temp.y < minPos.y)
		return;

	pos.x = temp.x;
	pos.y = temp.y;
}

void CameraManager::SetCameraMaxPos(int maxX, int maxY)
{
	maxPos.x = maxX;
	maxPos.y = maxY;
}

void CameraManager::SetCameraMinPos(int minX, int minY)
{
	minPos.x = minX;
	minPos.y = minY;
}
