#pragma once
#include "GameObject.h"
#include "CharacterSelectScene.h"

typedef void(CharacterSelectScene::* Callback)();
class Button : public GameObject
{
public:
	enum class eButtonState { Idle, Put, Click, None, };
	Button() = default;
	Button(CharacterSelectScene* _scene, Callback bf);
	virtual ~Button() = default;

	HRESULT Init(eButtonType type, POINT pos, int sizeX, int sizeY);
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	CharacterSelectScene* scene = nullptr;
	Callback buttonFunction = nullptr;

	POINT pos = {};
	int sizeX = 0;
	int sizeY = 0;
	Image* buttonIdleImage = nullptr;
	Image* buttonPutImage = nullptr;
	Image* buttonClickImage = nullptr;
	eButtonState state = eButtonState::None;

	Point renderPos = {};
	RECT collisionRect = {};
	
};
