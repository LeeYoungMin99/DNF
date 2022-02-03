#pragma once
#include "GameEntity.h"

class Scene;
class Component;
class GameObject : public IBehaviour
{
public:
	GameObject(Scene* scene, const wstring& tag);
	GameObject(GameObject* parent, const wstring& tag);
	virtual ~GameObject();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void					AddComponent(Component* component);
	void					RemoveComponent(Component* component);

	void					AddChild(GameObject* child)					{ _childs.push_back(child); }

	vector<Component*>&		GetComponents()								{ return _components; }
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
	void					SetIsActive(bool b);						

	void					AddX(const LONG& x)							{ _pos.x += x; }
	void					AddY(const LONG& y)							{ _pos.y += y; }

	GameObject*				GetChild(wstring tag);
	vector<GameObject*>&	GetChilds()									{ return _childs; }
	bool					GetIsActive()	const						{ return _bIsActive; }
	wstring					GetTag()		const						{ return _tag; }
	POINT					GetPosition()	const						{ return _pos; }
	LONG					GetX()			const						{ return _pos.x; }
	LONG					GetY()			const						{ return _pos.y; }
	Scene*					GetScene()		const						{ return _scene; }
protected:
	virtual	void OnEnable() { }
private:
	bool					_bIsActive = true;

	POINT					_pos = {};
	Scene*					_scene = nullptr;
	wstring					_tag = L"";

	vector<Component*>		_components = {};
	vector<GameObject*>		_childs = {};
};