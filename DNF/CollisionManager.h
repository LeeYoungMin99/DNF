#pragma once
#include "GameEntity.h"

class GameObject;
class CollisionManager : public GameEntity
{
public:
	~CollisionManager() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void AddObject(GameObject* obj);
	void SetObjects(const vector<GameObject*>& _objects);
private:
	vector<GameObject*> objects = {};
};
