#pragma once
#include "Scene.h"

class BmpImage;
class Seria;
class SeriaRoomScene : public Scene
{
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	BmpImage* mpBackground = nullptr;
	Seria* mpSeria = nullptr;
};
