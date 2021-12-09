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

void Scene::InitPos(POINTFLOAT charPos, POINT camPos, POINT maxCamPos, POINT minCamPos)
{
	mObjects[0]->SetAreaTag(mAreaTag);
	mObjects[0]->SetPos(charPos.x, charPos.y);
	MGR_CAM->SetCameraPos(camPos.x,camPos.y);
	MGR_CAM->SetCameraMaxPos(maxCamPos.x, maxCamPos.y);
	MGR_CAM->SetCameraMinPos(minCamPos.x, minCamPos.y);
}

bool Scene::cmp::operator()(const GameObject* lhs, const GameObject* rhs) const
{
	return lhs->GetPos().y > rhs->GetPos().y;
}
