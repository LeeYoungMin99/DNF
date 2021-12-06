#pragma once
#include "GameEntity.h"

class GameObject;
class Scene : public GameEntity
{
	struct cmp
	{
		bool operator()(const GameObject* lhs, const GameObject* rhs) const;
	};

public:
	virtual ~Scene() = default;

	virtual HRESULT Init() override { return S_OK; }
	virtual void Update() override {}
	virtual void Render(HDC hdc) override {}
	virtual void Release() override {}

protected:
	void AddObject(GameObject* obj, POINTFLOAT pos);

protected:
	vector<GameObject*> mObjects = {};
	priority_queue<GameObject*, vector<GameObject*>, cmp> mRenderOrder = {};
};
