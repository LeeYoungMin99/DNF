#pragma once

#include "stdafx.h"

#define WIN_START_POS_X	100
#define WIN_START_POS_Y	100
#define WIN_SIZE_X	1600
#define WIN_SIZE_Y	900
#define WIN_SIZE_X_HALF	800
#define WIN_SIZE_Y_HALF	450

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }
#define SAFE_UPDATAE(p) { if (p) { p->Update();} } 

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#define DELTA_TIME TimerManager::GetSingleton()->GetDeltaTime()
#define MGR_TIMER TimerManager::GetSingleton()
#define MGR_IMAGE BmpImageManager::GetSingleton()
#define MGR_SCENE SceneManager::GetSingleton()
#define MGR_KEY KeyManager::GetSingleton()
#define MGR_CAM CameraManager::GetSingleton()
#define GET_CAMERA_POS CameraManager::GetSingleton()->GetCameraPos()

#define FROM_FILE Image::FromFile 
#define SCENE_TAG SceneManager::eSceneTag

enum class eMoveDir { Left = -1, Right = 1, None, };

struct AnimationData
{
	AnimationData(const char* _path, int _maxFrame, float _motionSpeed, int _imageSizeX, int _imageSizeY, int _correctionPosX, int _correctionPosY, float _scale, bool _loop)
	{
		path = _path;
		maxFrame = _maxFrame;
		motionSpeed = _motionSpeed;
		imageSizeX = _imageSizeX;
		imageSizeY = _imageSizeY;
		imageFrameSizeX = _imageSizeX / _maxFrame;
		imageFrameSizeY = _imageSizeY;
		correctionPosX = _correctionPosX;
		correctionPosY = _correctionPosY;
		scale = _scale;
		loop = _loop;
	}

	const char* path = nullptr;
	int maxFrame = 0;
	float motionSpeed = 0;
	int imageSizeX = 0;
	int imageSizeY = 0;
	int imageFrameSizeX = 0;
	int imageFrameSizeY = 0;
	int correctionPosX = 0;
	int correctionPosY = 0;
	float scale = 0.0f;
	bool loop = false;
};