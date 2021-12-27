#include "stdafx.h"
#include "TownScene.h"

#include "Sprite.h"

#include "Player.h"
#include "Seria.h"
#include "Goblin.h"
#include "MapCollider.h"

#include "Component.h"
#include "RectColliderComponent.h"
#include "BodyCollisionComponent.h"
#include "AttackCollisionComponent.h"

#include "ImageManager.h"
#include "CameraManager.h"

void TownScene::Init()
{
	Sprite* seriaRoomBackground = new Sprite(L"Image/Elvengard/SeriaRoom/Background.png", this, L"SeriaRoomBackground");
	MapCollider* mapLeftCollider = new MapCollider({ 0,0,200,600 }, this, L"MapColliderLeft");
	MapCollider* mapTopCollider = new MapCollider({ 0,0,1200,400 }, this, L"MapColliderTop");
	MapCollider* mapRightCollider = new MapCollider({ 900,0,1200,600 }, this, L"MapColliderRight");
	MapCollider* mapBottomCollider = new MapCollider({ 0,600,1200,800 }, this, L"MapColliderBottom");

	Seria* seria = new Seria(this, L"Seria");
	Player* player = new Player(this, L"Player");

	Scene::Init();

	CameraManager::GetSingleton()->SetPlayer(player);
	CameraManager::GetSingleton()->SetCameraMaxPos(0, 0);
	CameraManager::GetSingleton()->SetCameraMinPos(-133, 0);
}

void TownScene::Update()
{
	Scene::Update();

#pragma region MovePhysics

	RECT collisionRect = {};
	RECT objCollider = {};
	RECT mapCollider = {};

	for (size_t i = 4; i < _objBodyCollider.size(); ++i)
	{
		objCollider = _objBodyCollider[i]->GetCollider()->GetRect();

		for (size_t j = 0; j < 4; ++j)
		{
			mapCollider = _objBodyCollider[j]->GetCollider()->GetRect();

			if (IntersectRect(&collisionRect, &objCollider, &mapCollider))
			{
				_objBodyCollider[i]->OnCollided(collisionRect);
			}
		}
	}

#pragma endregion

	CameraManager::GetSingleton()->Update();
}