#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"
#include "Scene.h"

GameObject::GameObject(Scene* scene, const wstring& tag)
	:
	_scene{ scene },
	_tag{ tag }
{
	_scene->AddObject(this);
}

GameObject::~GameObject() 
{
	Component* pTemp = nullptr;
	for (auto it = _components.begin(); it != _components.end(); )
	{
		pTemp = (*it);
		it = _components.erase(it);
		delete pTemp;
	}
	_components.clear();
	_scene = nullptr;
}

void GameObject::Init()
{
	for (Component* comp : _components)
	{
		comp->Init();
	}
}

void GameObject::Update()
{
	for (Component* comp : _components)
	{
		comp->Update();
	}
}

void GameObject::Render()
{
	for (Component* comp : _components)
	{
		comp->Render();
	}
}

void GameObject::Release()
{
	for (Component* comp : _components)
	{
		comp->Release();
	}
}

void GameObject::AddComponent(Component* component)
{
	_components.push_back(component);

	sort(_components.begin(), _components.end(),
		[](const Component* lhs, const Component* rhs)
		{
			return lhs->GetOrder() < rhs->GetOrder();
		});
}

void GameObject::RemoveComponent(Component* component)
{
	remove(_components.begin(), _components.end(), component);
}