#include "stdafx.h"
#include "BattleScene.h"

#include "Sprite.h"

#include "Player.h"
#include "Vinoshu.h"
#include "Meteor.h"
#include "MapCollider.h"

#include "Component.h"
#include "RectColliderComponent.h"
#include "BodyCollisionComponent.h"
#include "AttackCollisionComponent.h"

#include "ImageManager.h"
#include "CameraManager.h"

void BattleScene::Init()
{
	Sprite* farBackgorund = new Sprite(L"Image/Elvengard/BattleScene/FarBackground.png", this, L"FarBackground", 3);
	Sprite* middleBackgorund = new Sprite(L"Image/Elvengard/BattleScene/MiddleBackground.png", this, L"MiddleBackground", 2);
	Sprite* tile = new Sprite(L"Image/Elvengard/BattleScene/Tile.png", this, L"Tile", 1);

	MapCollider* mapLeftCollider = new MapCollider({ -200,0,0,600 }, this, L"MapColliderLeft");
	MapCollider* mapTopCollider = new MapCollider({ 0,0,1280,350 }, this, L"MapColliderTop");
	MapCollider* mapRightCollider = new MapCollider({ 1280,0,1544,600 }, this, L"MapColliderRight");
	MapCollider* mapBottomCollider = new MapCollider({ 0,600,1280,800 }, this, L"MapColliderBottom");

	Player* player = new Player(this, L"Player");
	Vinoshu* vinoshu = new Vinoshu(this, L"Monster");

	Scene::Init();

	CameraManager::GetSingleton()->SetPlayer(player);
	CameraManager::GetSingleton()->SetCameraMaxPos(0, 0);
	CameraManager::GetSingleton()->SetCameraMinPos(-213, 0);
}

void BattleScene::Update()
{
	for (GameObject* obj : _objects)
	{
		obj->Update();
		_objRenderOrder.push(obj);
	}

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

#pragma region AttckPhysics

	RECT attackObjCollider = {};
	RECT hitObjCollider = {};
	GameObject* hitObj = nullptr;
	GameObject* atkObj = nullptr;
	bool bPass = false;

	for (size_t i = 0; i < _objAttackCollider.size(); ++i)
	{
		atkObj = _objAttackCollider[i]->GetOwner();
		attackObjCollider = _objAttackCollider[i]->GetCollider()->GetRect();

		for (size_t j = 4; j < _objBodyCollider.size(); ++j)
		{
			hitObj = _objBodyCollider[j]->GetOwner();
			hitObjCollider = _objBodyCollider[j]->GetCollider()->GetRect();

			if (IntersectRect(&collisionRect, &attackObjCollider, &hitObjCollider))
			{
				if (_objBodyCollider[j]->GetZBottom() >= _objAttackCollider[i]->GetZTop())
				{
					bPass = true;
				}

				if (atkObj != hitObj && atkObj->GetTag() != hitObj->GetTag())
				{
					for (GameObject* obj : _objAttackCollider[i]->GetHitObjs())
					{
						if (obj == hitObj)
						{
							bPass = true;
							break;
						}
					}

					if (bPass == false)
					{
						_objBodyCollider[j]->OnCollided(_objAttackCollider[i]->GetStrikingPower(),_objAttackCollider[i]->GetFloatingPower(), _objAttackCollider[i]->GetResistance());
						_objAttackCollider[i]->AddHitObj(hitObj);
					}
				}
			}
		}
	}

#pragma endregion

	CameraManager::GetSingleton()->Update();
}

void BattleScene::Render()
{
	while (_objRenderOrder.empty() == false)
	{
		_objRenderOrder.top()->Render();
		_objRenderOrder.pop();
	}
}