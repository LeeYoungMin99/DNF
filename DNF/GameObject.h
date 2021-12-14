#pragma once
#include "GameEntity.h"

class Scene;
class Component;
class GameObject : public GameEntity
{
public:
	GameObject(Scene* scene, const std::wstring& tag);
	virtual ~GameObject() noexcept;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	std::vector<Component*>& GetComponents() noexcept;
	template <typename T>
	T* GetComponent()
	{
		static_assert(std::is_base_of_v<Component, T>, "T for GetComponent() must be component");

		for (Component* comp : mComponents)
		{
			if (dynamic_cast<T*>(comp))
			{
				return static_cast<T*>(comp);
			}
		}

		return nullptr;
	}

	void SetTag(const std::wstring& tag) noexcept;
	void SetPosition(POINT pos) noexcept;
	void SetPosition(LONG x, LONG y) noexcept;
	void SetX(LONG x) noexcept;
	void SetY(LONG y) noexcept;
	void AddX(LONG x) noexcept;
	void AddY(LONG y) noexcept;
	void GetAreaNumber(int areaNumber) noexcept;

	std::wstring	GetTag() const noexcept;
	POINT GetPosition() const noexcept;
	LONG GetX() const noexcept;
	LONG GetY() const noexcept;
	Scene* GetScene() noexcept;
	int GetAreaNumber() noexcept;
private:
	POINT mPos = {};
	Scene* mpScene = nullptr;
	int mAreaNumber = 0;
	std::wstring mTag = L"";
	std::vector<Component*> mComponents;
};