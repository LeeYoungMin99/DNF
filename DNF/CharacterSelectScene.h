#pragma once
#include "Scene.h"

class CharacterSelectScene : public Scene
{
public:
	using Scene::Scene;
	virtual ~CharacterSelectScene() noexcept = default;

	virtual void Init() override;
	virtual void Update() override;
};
