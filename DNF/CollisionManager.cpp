#include "stdafx.h"
#include "CollisionManager.h"
#include "GameObject.h"

HRESULT CollisionManager::Init()
{
	return S_OK;
}

void CollisionManager::Update()
{
	RECT intersectionRect;

	for (auto obj1 : objects)
	{
		for (auto obj2 : objects)
		{
			if (obj1 == obj2) { continue; }

			if (IntersectRect(&intersectionRect, ((*obj1).GetBodyCollisionRect()), ((*obj2).GetBodyCollisionRect())))
			{
				(*obj1).OnCollidedBody(intersectionRect);
			}
		}
	}

	for (auto obj1 : objects)
	{
		for (auto obj2 : objects)
		{
			if (obj1->GetObjectType() == obj2->GetObjectType()) { continue; }

			if (IntersectRect(&intersectionRect, ((*obj1).GetAttackCollisionRect()), ((*obj2).GetBodyCollisionRect())))
			{

			}
		}
	}
}

void CollisionManager::Render(HDC hdc)
{
}

void CollisionManager::Release()
{
}

void CollisionManager::AddObject(GameObject* obj)
{
	objects.push_back(obj);
}
