#pragma once
#include "Scene.h"

class BmpImage;
class ElvengardFieldScene : public Scene
{
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	BmpImage* mpElvengardFieldImage = nullptr;
	BmpImage* mpFarBackgroundImage = nullptr;
	BmpImage* mpMiddlerBackgroundImage = nullptr;

};
