#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (auto& obj : mObjects)
	{
		delete obj;
		obj = nullptr;
	}
	mObjects.clear();
}

void Scene::Init()
{
	for (GameObject* obj : mObjects)
	{
		obj->Init();
	}
}

void Scene::Update()
{
	for (GameObject* obj : mObjects)
	{
		obj->Update();
	}
}

void Scene::Render(HDC hdc)
{
	for (GameObject* obj : mObjects)
	{
		obj->Render(hdc);
	}
}

void Scene::Release()
{
	for (GameObject* obj : mObjects)
	{
		obj->Release();
	}
}

void Scene::AddObject(GameObject* obj)
{
	mObjects.push_back(obj);
}

void Scene::RemoveObject(const wstring& tag)
{
	remove_if(mObjects.begin(), mObjects.end(),
		[&tag](const GameObject* obj)
		{
			return obj->GetTag() == tag;
		});
}
