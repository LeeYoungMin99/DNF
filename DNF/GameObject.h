#pragma once
#include "GameEntity.h"

class Scene;
class Component;
class GameObject : public GameEntity
{
public:
	GameObject(Scene* scene, const wstring& tag);
	virtual ~GameObject();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	vector<Component*>& GetComponents() { return _components; }
	template <typename T>
	T* GetComponent()
	{
		static_assert(std::is_base_of_v<Component, T>, "T for GetComponent() must be component");

		for (Component* comp : _components)
		{
			if (dynamic_cast<T*>(comp))
			{
				return static_cast<T*>(comp);
			}
		}
		return nullptr;
	}

	void					SetTag(const wstring& tag)					{ _tag = tag; }
	void					SetPosition(const POINT& pos)				{ _pos = pos; }
	void					SetPosition(const LONG& x, const LONG& y)	{ _pos = POINT{ x, y }; }
	void					SetX(const LONG& x)							{ _pos.x = x; }
	void					SetY(const LONG& y)							{ _pos.y = y; }

	void					AddX(const LONG& x)							{ _pos.x += x; }
	void					AddY(const LONG& y)							{ _pos.y += y; }
	
	wstring					GetTag()		const						{ return _tag; }
	POINT					GetPosition()	const						{ return _pos; }
	LONG					GetX()			const						{ return _pos.x; }
	LONG					GetY()			const						{ return _pos.y; }
	Scene*					GetScene()		const						{ return _scene; }
private:
	POINT					_pos = {};
	Scene*					_scene = nullptr;
	wstring					_tag = L"";
	vector<Component*>		_components = {};
};