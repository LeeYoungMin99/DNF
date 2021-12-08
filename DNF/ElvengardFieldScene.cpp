#include "stdafx.h"
#include "ElvengardFieldScene.h"
#include "CollisionManager.h"

#include "DemonSlayer.h"
#include "SeriaTree.h"
#include "Sign.h"
#include "DungeonEntranceSign.h"
#include "Tent.h"
#include "SmarmyTree.h"
#include "BumpyTree.h"
#include "Blacksmith.h"

HRESULT ElvengardFieldScene::Init()
{
	mpFarBackgroundImage = MGR_IMAGE->AddImage("Image/Elvengard/FarBackground.bmp", 3360, 450);
	mpElvengardFieldImage = MGR_IMAGE->AddImage("Image/Elvengard/Field.bmp", 3360, 495, true, RGB(255, 0, 255));

	AddObject(new DemonSlayer, { 400.0f, 600.0f });
	AddObject(new SeriaTree, { 100.0f, 400.0f });
	AddObject(new Sign, { 780.0f, 490.0f });
	AddObject(new DungeonEntranceSign, { -500.0f, 550.0f });
	AddObject(new DungeonEntranceSign, { -650.0f, 950.0f });
	AddObject(new Tent, { -700.0f, 500.0f });
	AddObject(new SmarmyTree, { -550.0f, 385.0f });
	AddObject(new Blacksmith, { 1050.0f, 200.0f });
	AddObject(new BumpyTree, { 2100.0f, 389.0f });

	mpCollisionManager = new CollisionManager;
	mpCollisionManager->SetObjects(mObjects);

	MGR_CAM->SetCameraMaxPos((3360 / 2) - 800, 0);
	MGR_CAM->SetCameraMinPos(-(3360 / 2) + 800, 0);
	MGR_CAM->SetCameraPos(-300, 0);

	return S_OK;
}

void ElvengardFieldScene::Update()
{
	if (Input::GetButton('A')) { MGR_CAM->AddCameraPos(10, 0); }
	if (Input::GetButton('D')) { MGR_CAM->AddCameraPos(-10, 0); }
	
	for (auto obj : mObjects) { obj->Update(); }
	
	mpCollisionManager->Update();

	for (auto obj : mObjects) { mRenderOrder.push(obj); }
}

void ElvengardFieldScene::Render(HDC hdc)
{
	mpFarBackgroundImage->Render(hdc, WIN_SIZE_X_HALF + GET_CAMERA_POS.x, 225 + GET_CAMERA_POS.y);
	mpElvengardFieldImage->Render(hdc, WIN_SIZE_X_HALF + GET_CAMERA_POS.x, 655 + GET_CAMERA_POS.y);

	while (false == mRenderOrder.empty())
	{
		mRenderOrder.top()->Render(hdc);
		mRenderOrder.pop();
	}
}

void ElvengardFieldScene::Release()
{
	SAFE_RELEASE(mpCollisionManager);

	for (auto obj : mObjects) { SAFE_RELEASE(obj); }
}
