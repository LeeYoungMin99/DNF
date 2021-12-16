#pragma once
#include "GameEntity.h"

class GameObject;
class Scene : public GameEntity
{
protected:
	struct cmp
	{
		bool operator()(const GameObject* lhs, const GameObject* rhs) const;
	};
public:
	Scene() = default;
	virtual ~Scene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void				AddObject(GameObject* obj);
	void				RemoveObject(const wstring& tag);
protected:
	vector<GameObject*>		mObjects;
};
