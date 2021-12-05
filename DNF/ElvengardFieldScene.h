#pragma once
#include "Scene.h"

class BmpImage;
class DemonSlayer;
class CollisionManager;
class SeriaTree;
class ElvengardFieldScene : public Scene
{
public:
	~ElvengardFieldScene() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	BmpImage* mpElvengardFieldImage = nullptr;
	BmpImage* mpFarBackgroundImage = nullptr;
	BmpImage* mpMiddlerBackgroundImage = nullptr;

	CollisionManager* mpCollisionManager = nullptr;
	SeriaTree* mpSeriaTree = nullptr;

	DemonSlayer* mpMyCharacter = nullptr;
};
