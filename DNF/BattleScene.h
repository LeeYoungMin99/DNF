#pragma once
#include "Scene.h"

class BattleScene : public Scene
{
public:
	using Scene::Scene;
	virtual ~BattleScene() = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

