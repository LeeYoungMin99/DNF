#pragma once
#include "GameEntity.h"

class GameObject;
class CollisionManager : public GameEntity
{
public:
	CollisionManager() = default;
	virtual ~CollisionManager() noexcept = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
private:
	vector<GameObject*> mpObjects = {};
};

