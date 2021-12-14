#include "stdafx.h"
#include "TownScene.h"

#include "Player.h"

void TownScene::Init()
{
	Player* player = new Player(this, L"Player");

	player->SetPosition({ 500,600 });
	player->SetMoveSpeed(200);

	Scene::Init();
}

void TownScene::Update()
{
	Scene::Update();
}

void TownScene::Render()
{
	Scene::Render();
}
