#pragma once
#include "Singleton.h"

class CameraManager : public Singleton<CameraManager>
{
public:
	virtual ~CameraManager() = default;

	POINT GetCameraPos();
	void SetCameraPos(int posX,int posY);
	void AddCameraPos(int posX, int posY);
	void SetCameraMaxPos(int maxX, int maxY);
	void SetCameraMinPos(int minX, int minY);

private:
	POINT pos = {};
	POINT maxPos = {};
	POINT minPos = {};

	const int camSizeX = WIN_SIZE_X;
	const int camSizeY = WIN_SIZE_Y;
};
