#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"
#include "Scene.h"

GameObject::GameObject(Scene* scene, const wstring& tag)
	:
	mpScene{ scene },
	mTag{ tag }
{
	mpScene->AddObject(this);
}

GameObject::~GameObject() noexcept
{
	Component* pTemp = nullptr;
	for (auto it = mComponents.begin(); it != mComponents.end(); )
	{
		pTemp = (*it);
		it = mComponents.erase(it);
		delete pTemp;
	}
	mComponents.clear();
	mpScene = nullptr;
}

void GameObject::Init()
{
	for (Component* comp : mComponents)
	{
		comp->Init();
	}
}

void GameObject::Update()
{
	for (Component* comp : mComponents)
	{
		comp->Update();
	}
}

void GameObject::Render()
{
	for (Component* comp : mComponents)
	{
		comp->Render();
	}
}

void GameObject::Release()
{
	for (Component* comp : mComponents)
	{
		comp->Release();
	}
}

void GameObject::AddComponent(Component* component)
{
	mComponents.push_back(component);

	sort(mComponents.begin(), mComponents.end(),
		[](const Component* lhs, const Component* rhs)
		{
			return lhs->GetOrder() < rhs->GetOrder();
		});
}

void GameObject::RemoveComponent(Component* component)
{
	remove(mComponents.begin(), mComponents.end(), component);
}

void GameObject::SetTag(const wstring& tag) noexcept
{
	mTag = tag;
}

void GameObject::SetPosition(POINT pos) noexcept
{
	mPos = pos;
}

void GameObject::SetPosition(LONG x, LONG y) noexcept
{
	mPos = POINT{ x, y };
}

wstring GameObject::GetTag() const noexcept
{
	return mTag;
}

POINT GameObject::GetPosition() const noexcept
{
	return mPos;
}

void GameObject::SetX(LONG x) noexcept
{
	mPos.x = x;
}

LONG GameObject::GetX() const noexcept
{
	return mPos.x;
}

void GameObject::SetY(LONG y) noexcept
{
	mPos.y = y;
}

void GameObject::AddX(LONG x) noexcept
{
	mPos.x += x;
}

void GameObject::AddY(LONG y) noexcept
{
	mPos.y += y;
}

void GameObject::SetAreaNumber(int areaNumber) noexcept
{
	mAreaNumber = areaNumber;
}

LONG GameObject::GetY() const noexcept
{
	return mPos.y;
}

Scene* GameObject::GetScene() noexcept
{
	return mpScene;
}

int GameObject::GetAreaNumber() noexcept
{
	return mAreaNumber;
}

vector<Component*>& GameObject::GetComponents() noexcept
{
	return mComponents;
}
