#include "stdafx.h"
#include "TownScene.h"

#include "Player.h"
#include "Seria.h"
#include "Sprite.h"

#include "ImageManager.h"

void TownScene::Init()
{
	Sprite* seriaRoomBackground = new Sprite(this, L"SeriaRoomBackground");
	seriaRoomBackground->SetImage(ImageManager::GetSingleton()->FindImage(L"Image/Elvengard/SeriaRoom/Background.png"));

	mpPlayer = new Player(this, L"Player");
	Seria* seria = new Seria(this, L"Seria");

	Scene::Init();

	seriaRoomBackground->SetAreaNumber((int)eAreaTag::SeriaRoom);
	seria->SetAreaNumber((int)eAreaTag::SeriaRoom);

	mpPlayer->SetPosition({ 533,500 });
	mpPlayer->SetMoveSpeed(200);
	mpPlayer->SetAreaNumber((int)eAreaTag::SeriaRoom);

}

void TownScene::Update()
{
	int playerCurrArea = mpPlayer->GetAreaNumber();

	//�׽�Ʈ�ڵ�
	if (Input::GetButtonDown('3')) { mpPlayer->SetAreaNumber(!((bool)playerCurrArea)); }
	if (Input::GetButtonDown('4')) { mpPlayer->AddHP(-10); }

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
