#pragma once
#pragma once
#include "Scene.h"

class Player;
class TownScene : public Scene
{
public:
	enum class eAreaTag { SeriaRoom, Field, DungeonEntrance };
public:
	using Scene::Scene;
	virtual ~TownScene() = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	priority_queue<GameObject*, vector<GameObject*>, cmp> mpRenderOrder = {};
	Player* mpPlayer = nullptr;
};

