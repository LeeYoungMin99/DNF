#pragma once
#include "Scene.h"

class BmpImage;
class CollisionManager;
class Seria;
class TownScene : public Scene
{
	enum class eAreaTag { None, SeriaRoom, Field, DungeonEntrance, DungeonSelect };
public:
	virtual ~TownScene() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	BmpImage* mpBackground = nullptr;
	BmpImage* mpMiddlerBackgroundImage = nullptr;
	BmpImage* mpFarBackgroundImage = nullptr;

	BmpImage* mpElvengardFieldImage = nullptr;


	CollisionManager* mpCollisionManager = nullptr;
};

