#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"

void Scene::AddObject(GameObject* obj, POINTFLOAT pos)
{
	mObjects.push_back(obj);
	mObjects[mObjects.size() - 1]->Init();
	mObjects[mObjects.size() - 1]->SetPos(pos.x, pos.y);
}

bool Scene::cmp::operator()(const GameObject* lhs, const GameObject* rhs) const
{
	return lhs->GetPos().y > rhs->GetPos().y;
}
