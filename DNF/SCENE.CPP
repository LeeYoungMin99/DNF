#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"
#include "Gate.h"

void Scene::AddObject(GameObject* obj, POINTFLOAT pos, int areaTag)
{
	obj->Init();
	obj->SetPos(pos.x, pos.y);
	obj->SetAreaTag(areaTag);

	mObjects.push_back(obj);
}

void Scene::AddGate(Gate* obj, POINTFLOAT pos, int areaTag, Scene* scene, CollisionManager* collisionManager, int connectedArea)
{
	obj->Init();
	obj->SetPos(pos.x, pos.y);
	obj->SetAreaTag(areaTag);
	obj->SetCurrScene(scene);
	obj->SetCollisionManager(collisionManager);
	obj->SetConnectedArea(connectedArea);

	mObjects.push_back(obj);
}

bool Scene::cmp::operator()(const GameObject* lhs, const GameObject* rhs) const
{
	return lhs->GetPos().y > rhs->GetPos().y;
}
