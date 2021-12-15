#include "stdafx.h"
#include "TownScene.h"

#include "Player.h"
#include "Sprite.h"

#include "ImageManager.h"

void TownScene::Init()
{
	Sprite* seriaRoomBackground = new Sprite(this, L"SeriaRoomBackground");
	seriaRoomBackground->SetImage(ImageManager::GetSingleton()->FindImage(L"Image/Elvengard/SeriaRoom/Background.png"));

	mpPlayer = new Player(this, L"Player");

	Scene::Init();

	seriaRoomBackground->SetAreaNumber((int)eAreaTag::SeriaRoom);

	mpPlayer->SetPosition({ 500,500 });
	mpPlayer->SetMoveSpeed(200);
	mpPlayer->SetAreaNumber((int)eAreaTag::SeriaRoom);
}

void TownScene::Update()
{
	int playerCurrArea = mpPlayer->GetAreaNumber();

	if (Input::GetButtonDown('3'))
	{
		//테스트코드
		mpPlayer->SetAreaNumber(!((bool)playerCurrArea));
	}


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
