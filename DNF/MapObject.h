#pragma once
#include "GameObject.h"

class MapObject : public GameObject
{
public:
	virtual ~MapObject() = default;

	virtual HRESULT Init() override			{ return S_OK; }
	virtual void Update() override			{}
	virtual void Render(HDC hdc) override	{}
	virtual void Release() override			{}
private:
};
