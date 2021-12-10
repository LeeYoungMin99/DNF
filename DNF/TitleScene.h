#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	using Scene::Scene;
	virtual ~TitleScene() noexcept = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
};
