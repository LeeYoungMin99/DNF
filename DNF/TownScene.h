#pragma once
#include "Scene.h"

class TownScene : public Scene
{
public:
	using Scene::Scene;
	virtual ~TownScene() = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

