#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"
#include "Scene.h"

GameObject::GameObject(Scene* scene, const wstring& tag)
	: _scene{ scene }, _tag{ tag }
{
	_scene->AddObject(this);
}

GameObject::GameObject(GameObject* parent, const wstring& tag)
	: _scene{ parent->GetScene() }, _tag{ tag }
{
	parent->AddChild(this);
}

GameObject::~GameObject()
{
	Component* comp = nullptr;
	for (auto it = _components.begin(); it != _components.end();)
	{
		comp = (*it);
		it = _components.erase(it);
		SAFE_RELEASE(comp);
	}
	_components.clear();

	GameObject* child = nullptr;
	for (auto it = _childs.begin(); it != _childs.end();)
	{
		child = (*it);
		it = _childs.erase(it);
		SAFE_RELEASE(child);
	}
	_childs.clear();

	_scene = nullptr;
}

void GameObject::Init()
{
	for (Component* comp : _components)
	{
		comp->Init();
	}

	for (GameObject*& child : _childs)
	{
		child->Init();
	}
}

void GameObject::Update()
{
	if (false == _bIsActive) { return; }

	for (Component* comp : _components)
	{
		comp->Update();
	}

	for (GameObject*& child : _childs)
	{
		child->Update();
	}
}

void GameObject::Render()
{
	if (_bIsActive == false) { return; }

	for (Component*& comp : _components)
	{
		comp->Render();
	}

	for (GameObject*& child : _childs)
	{
		child->Render();
	}
}

void GameObject::Release()
{
	for (Component* comp : _components)
	{
		comp->Release();
	}

	for (GameObject* child : _childs)
	{
		child->Release();
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

GameObject* GameObject::GetChild(wstring tag)
{
	for (GameObject* child : _childs)
	{
		if (child->GetTag() == tag)
		{
			return child;
		}
	}
	return nullptr;
}

void GameObject::SetIsActive(bool b)
{
	if (b == _bIsActive)
	{
		return;
	}

	if (_bIsActive == false)
	{
		OnEnable();
	}

	_bIsActive = b;
}