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
	float mRotateAngle = 0.0f;
	float mElapsedTime = 0.0f;

	Image* mpTitleImage = nullptr;
	Image* mpLoadingImage = nullptr;
	Image* mpLoadingRotateImage = nullptr;
	Image* mpNeopleImage = nullptr;
	Image* mpLoadingBelt = nullptr;
};
