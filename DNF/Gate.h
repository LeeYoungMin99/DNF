#pragma once
#include "MapObject.h"

class Animation;
class Scene;
class CollisionManager;
class Gate : public MapObject
{
public:
	~Gate() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	virtual void OnCollidedBody(RECT intersectionRect);

	void SetConnectedArea(int area) { mConnectedArea = area; }
	void SetCurrScene(Scene* scene) { mpCurrScene = scene; }
	void SetCollisionManager(CollisionManager* mgr) { mpCollisionManager = mgr; }
private:
	Animation* mpGate = nullptr;

	int mConnectedArea = 0;
	Scene* mpCurrScene = nullptr;
	CollisionManager* mpCollisionManager = nullptr;

	const int IMAGE_SIZE_X = 214;
	const int IMAGE_SIZE_Y = 78;
	const int BODY_COLLISION_LEFT = -40;
	const int BODY_COLLISION_TOP = -10;
	const int BODY_COLLISION_RIGHT = 140;
	const int BODY_COLLISION_BOTTOM = 50;
};