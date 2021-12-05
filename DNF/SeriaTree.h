#pragma once
#include "MapObject.h"

class BmpImage;
class SeriaTree : public MapObject
{
public:
	virtual ~SeriaTree() = default;;

	virtual HRESULT Init();
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	BmpImage* mpSeriaTree = nullptr;
};