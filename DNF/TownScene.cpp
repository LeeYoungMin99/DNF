#include "stdafx.h"
#include "TownScene.h"
#include "CollisionManager.h"

#include "DemonSlayer.h"
#include "Seria.h"
#include "SeriaTree.h"
#include "Sign.h"
#include "DungeonEntranceSign.h"
#include "Tent.h"
#include "SmarmyTree.h"
#include "BumpyTree.h"
#include "Blacksmith.h"
#include "Gate.h"

HRESULT TownScene::Init()
{
	mpBackground = MGR_IMAGE->AddImage("Image/SeriaRoom/SeriaRoom.bmp", 1600, 939);
	mpFarBackgroundImage = MGR_IMAGE->AddImage("Image/Elvengard/FarBackground.bmp", 3360, 450);
	mpElvengardFieldImage = MGR_IMAGE->AddImage("Image/Elvengard/Field.bmp", 3360, 495, true, RGB(255, 0, 255));

	mpCollisionManager = new CollisionManager;

	AddObject(new DemonSlayer, { 800.0f, 850.0f }, (int)eAreaTag::SeriaRoom);
	AddObject(new Seria, { WIN_SIZE_X_HALF, WIN_SIZE_Y_HALF - 58 }, (int)eAreaTag::SeriaRoom);
	AddGate(new Gate, { 1400,700 }, (int)eAreaTag::SeriaRoom, this, mpCollisionManager, (int)eAreaTag::Field);

	AddObject(new SeriaTree, { 100.0f, 400.0f }, (int)eAreaTag::Field);
	AddObject(new SmarmyTree, { 400.0f, 335.0f }, (int)eAreaTag::Field);
	AddObject(new Sign, { 780.0f, 490.0f }, (int)eAreaTag::Field);
	AddObject(new DungeonEntranceSign, { -500.0f, 550.0f }, (int)eAreaTag::Field);
	AddObject(new DungeonEntranceSign, { -650.0f, 950.0f }, (int)eAreaTag::Field);
	AddObject(new Tent, { -700.0f, 500.0f }, (int)eAreaTag::Field);
	AddObject(new SmarmyTree, { -550.0f, 385.0f }, (int)eAreaTag::Field);
	AddObject(new Blacksmith, { 1050.0f, 200.0f }, (int)eAreaTag::Field);
	AddObject(new BumpyTree, { 2050.0f, 390.0f }, (int)eAreaTag::Field);
	AddObject(new BumpyTree, { 2600.0f, 390.0f }, (int)eAreaTag::Field);
	AddGate(new Gate, { 2000,800 }, (int)eAreaTag::Field, this, mpCollisionManager, (int)eAreaTag::SeriaRoom);

	mAreaTag = (int)eAreaTag::SeriaRoom;
	mPreviousArea = mAreaTag;

	MGR_CAM->SetCameraMaxPos(0, 0);
	MGR_CAM->SetCameraMinPos(0, 0);
	MGR_CAM->SetCameraPos(0, 0);

	mpCollisionManager->SetObjects(mObjects);
	mpCollisionManager->SetAreaTag(mAreaTag);
	mpCollisionManager->SetNextAreaTag(mAreaTag);

	return S_OK;
}

void TownScene::Update()
{
	if (Input::GetButton('A')) { MGR_CAM->AddCameraPos(10, 0); }
	if (Input::GetButton('D')) { MGR_CAM->AddCameraPos(-10, 0); }

	if (mAreaTag != mPreviousArea)
	{
		switch ((eAreaTag)mPreviousArea)
		{
		case eAreaTag::SeriaRoom:
			if (mAreaTag == (int)eAreaTag::Field)
			{
				mObjects[0]->SetPos(500.0f, 650.0f);
				mObjects[0]->SetAreaTag(mAreaTag);
				MGR_CAM->SetCameraMaxPos((3360 / 2) - 800, 0);
				MGR_CAM->SetCameraMinPos(-(3360 / 2) + 800, 0);
				MGR_CAM->SetCameraPos(-300, 0);
			}
			break;
		case eAreaTag::Field:
			if (mAreaTag == (int)eAreaTag::SeriaRoom)
			{
				mObjects[0]->SetPos(800.0f, 850.0f);
				mObjects[0]->SetAreaTag(mAreaTag);
				MGR_CAM->SetCameraMaxPos(0, 0);
				MGR_CAM->SetCameraMinPos(0, 0);
				MGR_CAM->SetCameraPos(0, 0);
			}
			if (mAreaTag == (int)eAreaTag::DungeonEntrance)
			{
				MGR_CAM->SetCameraMaxPos(0, 0);
				MGR_CAM->SetCameraMinPos(0, 0);
				MGR_CAM->SetCameraPos(0, 0);
			}
			break;
		case eAreaTag::DungeonEntrance:
			if (mAreaTag == (int)eAreaTag::Field)
			{
				MGR_CAM->SetCameraMaxPos(0, 0);
				MGR_CAM->SetCameraMinPos(0, 0);
				MGR_CAM->SetCameraPos(0, 0);
			}
			if (mAreaTag == (int)eAreaTag::DungeonSelect)
			{
				MGR_CAM->SetCameraMaxPos(0, 0);
				MGR_CAM->SetCameraMinPos(0, 0);
				MGR_CAM->SetCameraPos(0, 0);
			}
			break;
		case eAreaTag::DungeonSelect:
			if (mAreaTag == (int)eAreaTag::DungeonEntrance)
			{
				MGR_CAM->SetCameraMaxPos(0, 0);
				MGR_CAM->SetCameraMinPos(0, 0);
				MGR_CAM->SetCameraPos(0, 0);
			}
		case eAreaTag::None:
		default:
			break;
		}

		mPreviousArea = mAreaTag;
	}

	for (auto obj : mObjects) { if (obj->GetAreaTag() == mAreaTag) { obj->Update(); } }

	mpCollisionManager->Update();

	for (auto obj : mObjects) { if (obj->GetAreaTag() == mAreaTag) { mRenderOrder.push(obj); } }

}

void TownScene::Render(HDC hdc)
{
	if (mAreaTag == (int)eAreaTag::SeriaRoom)
	{
		mpBackground->Render(hdc, WIN_SIZE_X_HALF, WIN_SIZE_Y_HALF);
	}
	else if (mAreaTag == (int)eAreaTag::Field)
	{
		mpFarBackgroundImage->Render(hdc, WIN_SIZE_X_HALF + GET_CAMERA_POS.x, 225 + GET_CAMERA_POS.y);
		mpElvengardFieldImage->Render(hdc, WIN_SIZE_X_HALF + GET_CAMERA_POS.x, 655 + GET_CAMERA_POS.y);
	}

	while (false == mRenderOrder.empty())
	{
		mRenderOrder.top()->Render(hdc);
		mRenderOrder.pop();
	}
}

void TownScene::Release()
{
	SAFE_RELEASE(mpCollisionManager);

	for (auto obj : mObjects) { SAFE_RELEASE(obj); }
}
