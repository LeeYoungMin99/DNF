#pragma once
#include "Scene.h"
class ElvengardScene : public Scene
{
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:

};
