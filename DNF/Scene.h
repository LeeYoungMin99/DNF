#pragma once
#include "GameEntity.h"

class GameObject;
class CollisionManager;
class Gate;
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
	virtual void SetAreaTag(int area) { mAreaTag = area; }
protected:
	void AddObject(GameObject* obj, POINTFLOAT pos, int areaTag);
	void AddGate(Gate* obj, POINTFLOAT pos, int areaTag, Scene* scene, CollisionManager* collisionManager, int connectedArea);
	void InitPos(POINTFLOAT charPos, POINT camPos, POINT maxCamPos, POINT minCamPos);

protected:
	int mAreaTag = 0;
	int mPreviousArea = 0;

	vector<GameObject*> mObjects = {};
	priority_queue<GameObject*, vector<GameObject*>, cmp> mRenderOrder = {};
};
