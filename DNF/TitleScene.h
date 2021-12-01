#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	virtual ~TitleScene() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	float rotateAngle = 0.0f;
	float elapsedTime = 0.0f;

	Image* titleImage = nullptr;
	Image* loadingImage = nullptr;
	Image* loadingRotateImage = nullptr;
	Image* neopleImage = nullptr;
	Image* loadingBelt = nullptr;
};
