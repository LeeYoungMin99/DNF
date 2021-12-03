#include "stdafx.h"
#include "SeriaRoomScene.h"
#include "BmpImage.h"
#include "Seria.h"

HRESULT SeriaRoomScene::Init()
{
	mpBackground = MGR_IMAGE->AddImage("Image/SeriaRoom/SeriaRoom.bmp", 1600, 939);
	mpSeria = new Seria;
	mpSeria->Init();

	return S_OK;
}

void SeriaRoomScene::Update()
{
	mpSeria->Update();
}

void SeriaRoomScene::Render(HDC hdc)
{
	mpBackground->Render(hdc, WIN_SIZE_X_HALF, WIN_SIZE_Y_HALF);
	mpSeria->Render(hdc);
}

void SeriaRoomScene::Release()
{
	SAFE_RELEASE(mpSeria);
}
