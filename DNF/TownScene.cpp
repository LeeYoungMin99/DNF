#include "stdafx.h"
#include "TownScene.h"

#include "Player.h"
#include "Seria.h"
#include "Sprite.h"

#include "ImageManager.h"
#include "CameraManager.h"
#include "CollisionManager.h"

void TownScene::Init()
{
	Sprite* seriaRoomBackground = new Sprite(this, L"SeriaRoomBackground");
	seriaRoomBackground->SetImage(ImageManager::GetSingleton()->FindImage(L"Image/Elvengard/SeriaRoom/Background.png"));

	mpPlayer = new Player(this, L"Player");
	Seria* seria = new Seria(this, L"Seria");

	Scene::Init();

	seriaRoomBackground->SetAreaNumber((int)eAreaTag::SeriaRoom);
	seria->SetAreaNumber((int)eAreaTag::SeriaRoom);

	mpPlayer->SetPosition({ 600,500 });
	mpPlayer->SetMoveSpeed(200);
	mpPlayer->SetAreaNumber((int)eAreaTag::SeriaRoom);

	CameraManager::GetSingleton()->SetCameraMaxPos(0, 0);
	CameraManager::GetSingleton()->SetCameraMinPos(-133, 0);
}

void TownScene::Update()
{
	int playerCurrArea = mpPlayer->GetAreaNumber();

	//테스트코드
	if (Input::GetButtonDown('2')) { mpPlayer->SetAreaNumber(!((bool)playerCurrArea)); }

	for (GameObject* obj : mObjects)
	{
		if (playerCurrArea == obj->GetAreaNumber())
		{
			obj->Update();
			mpRenderOrder.push(obj);
		}
	}
}

void TownScene::Render()
{
	while (mpRenderOrder.empty() == false)
	{
		mpRenderOrder.top()->Render();
		mpRenderOrder.pop();
	}
}
