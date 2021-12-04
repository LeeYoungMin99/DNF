#include "stdafx.h"
#include "ElvengardFieldScene.h"

HRESULT ElvengardFieldScene::Init()
{
	mpFarBackgroundImage = MGR_IMAGE->AddImage("Image/Elvengard/FarBackground.bmp", 3360, 450);
	mpElvengardFieldImage = MGR_IMAGE->AddImage("Image/Elvengard/Field.bmp", 3360, 495, true, RGB(255, 0, 255));

	MGR_CAM->SetCameraMaxPos((3360 / 2) - 700, 0);
	MGR_CAM->SetCameraMinPos(-(3360 / 2) + 700, 0);

	return S_OK;
}

void ElvengardFieldScene::Update()
{
	if (MGR_KEY->IsStayKeyDown('A'))
	{
		MGR_CAM->AddCameraPos(10, 0);
	}
	if (MGR_KEY->IsStayKeyDown('D'))
	{
		MGR_CAM->AddCameraPos(-10, 0);
	}
}

void ElvengardFieldScene::Render(HDC hdc)
{
	mpFarBackgroundImage->Render(hdc, WIN_SIZE_X_HALF + GET_CAMERA_POS.x, 225 + GET_CAMERA_POS.y);
	mpElvengardFieldImage->Render(hdc, WIN_SIZE_X_HALF + GET_CAMERA_POS.x, 655 + GET_CAMERA_POS.y);
}

void ElvengardFieldScene::Release()
{
}
