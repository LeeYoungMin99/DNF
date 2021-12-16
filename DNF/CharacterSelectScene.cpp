#include "stdafx.h"
#include "CharacterSelectScene.h"
#include "GameObject.h"

#include "RectComponent.h"
#include "SpriteComponent.h"
#include "TextComponent.h"

#include "GameStartButton.h"
#include "GameShutDownButton.h"
#include "CreateCharacterButton.h"
#include "DeleteCharacterButton.h"
#include "ImageManager.h"
#include "Sprite.h"
#include "Image.h"

void CharacterSelectScene::Init()
{
	Sprite* backgroundImg = new Sprite(this, L"BackGround");
	Sprite* slotBackgroundImg = new Sprite(this, L"SlotBackGround");

	CreateCharacterButton* createCharacterButton = new CreateCharacterButton(this, L"CreateCharacterButton");
	DeleteCharacterButton* deleteCharacterButton = new DeleteCharacterButton(this, L"DeleteCharacterStartButton");
	GameStartButton* gameStartButton = new GameStartButton(this, L"GameStartButton");
	GameShutDownButton* gameShutDownButton = new GameShutDownButton(this, L"GameShutDownButton");

	Scene::Init();
	backgroundImg->SetImage(ImageManager::GetSingleton()->FindImage(L"Image/CharacterSelectScene/Background.png"));
	slotBackgroundImg->SetImage(ImageManager::GetSingleton()->FindImage(L"Image/CharacterSelectScene/SlotBackground.png"));
	slotBackgroundImg->SetY(600 - 268);
}
