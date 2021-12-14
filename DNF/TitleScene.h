#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	using Scene::Scene;
	virtual ~TitleScene() = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
private:
};
