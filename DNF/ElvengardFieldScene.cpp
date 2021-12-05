#include "stdafx.h"
#include "ElvengardFieldScene.h"
#include "CollisionManager.h"
#include "DemonSlayer.h"
#include "SeriaTree.h"

HRESULT ElvengardFieldScene::Init()
{
	mpFarBackgroundImage = MGR_IMAGE->AddImage("Image/Elvengard/FarBackground.bmp", 3360, 450);
	mpElvengardFieldImage = MGR_IMAGE->AddImage("Image/Elvengard/Field.bmp", 3360, 495, true, RGB(255, 0, 255));

	mpCollisionManager = new CollisionManager;
	mpMyCharacter = new DemonSlayer;
	mpMyCharacter->Init();
	mpMyCharacter->SetPos(0, 400);
	mpCollisionManager->AddObject(mpMyCharacter);

	mpSeriaTree = new SeriaTree;
	mpSeriaTree->Init();
	mpSeriaTree->SetPos(-200.0f, 450.0f);
	mpCollisionManager->AddObject(mpSeriaTree);


	MGR_CAM->SetCameraMaxPos((3360 / 2) - 800, 0);
	MGR_CAM->SetCameraMinPos(-(3360 / 2) + 800, 0);

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

	mpSeriaTree->Update();
	mpMyCharacter->Update();

	mpCollisionManager->Update();
}

void ElvengardFieldScene::Render(HDC hdc)
{
	mpFarBackgroundImage->Render(hdc, WIN_SIZE_X_HALF + GET_CAMERA_POS.x, 225 + GET_CAMERA_POS.y);
	mpElvengardFieldImage->Render(hdc, WIN_SIZE_X_HALF + GET_CAMERA_POS.x, 655 + GET_CAMERA_POS.y);
	mpSeriaTree->Render(hdc);
	mpMyCharacter->Render(hdc);
}

void ElvengardFieldScene::Release()
{
	SAFE_RELEASE(mpSeriaTree);
	SAFE_RELEASE(mpMyCharacter);
	SAFE_RELEASE(mpCollisionManager);
}
