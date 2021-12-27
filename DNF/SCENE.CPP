#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"

Scene::~Scene()
{
	for (auto& obj : _objects)
	{
		delete obj;
		obj = nullptr;
	}
	_objects.clear();
}

void Scene::Init()
{
	for (GameObject* obj : _objects)
	{
		obj->Init();
	}
}

void Scene::Update()
{
	for (GameObject* obj : _objects)
	{
		obj->Update();
	}
}

void Scene::Render()
{
	for (GameObject* obj : _objects)
	{
		obj->Render();
	}
}

void Scene::Release()
{
	for (GameObject* obj : _objects)
	{
		obj->Release();
	}
}

void Scene::AddObject(GameObject* obj)
{
	_objects.push_back(obj);
}

void Scene::AddBodyCollider(BodyCollisionComponent* bodyCollider)
{
	_objBodyCollider.push_back(bodyCollider);
}

void Scene::AddAttackCollider(AttackCollisionComponent* atkCollider)
{
	_objAttackCollider.push_back(atkCollider);
}

void Scene::RemoveObject(const wstring& tag)
{
	remove_if(_objects.begin(), _objects.end(),
		[&tag](const GameObject* obj)
		{
			return obj->GetTag() == tag;
		});
}

bool Scene::cmp::operator()(const GameObject* lhs, const GameObject* rhs) const
{
	return lhs->GetY() > rhs->GetY();
}

