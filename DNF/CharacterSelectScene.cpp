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

	createCharacterButton->SetPosition({ 318 ,559 });
	deleteCharacterButton->SetPosition({ 384 ,559 });
	gameStartButton->SetPosition({ 450,548 });
	gameShutDownButton->SetPosition({ 630,559 });
	
	createCharacterButton->GetComponent<RectComponent>()->SetRect({ createCharacterButton->GetX(),createCharacterButton->GetY(),createCharacterButton->GetX() + 56,createCharacterButton->GetY() + 24 });
	deleteCharacterButton->GetComponent<RectComponent>()->SetRect({ deleteCharacterButton->GetX(),deleteCharacterButton->GetY(),deleteCharacterButton->GetX() + 56,deleteCharacterButton->GetY() + 24 });
	gameStartButton->GetComponent<RectComponent>()->SetRect({ gameStartButton->GetX(),gameStartButton->GetY(),gameStartButton->GetX() + 170,gameStartButton->GetY() + 47 });
	gameShutDownButton->GetComponent<RectComponent>()->SetRect({ gameShutDownButton->GetX(),gameShutDownButton->GetY(),gameShutDownButton->GetX() + 56,gameShutDownButton->GetY() + 24 });
	
	createCharacterButton->GetComponent<TextComponent>()->SetRect({ createCharacterButton->GetX(),createCharacterButton->GetY(),createCharacterButton->GetX() + 56,createCharacterButton->GetY() + 24 });
	deleteCharacterButton->GetComponent<TextComponent>()->SetRect({ deleteCharacterButton->GetX(),deleteCharacterButton->GetY(),deleteCharacterButton->GetX() + 56,deleteCharacterButton->GetY() + 24 });
	gameShutDownButton->GetComponent<TextComponent>()->SetRect({ gameShutDownButton->GetX(),gameShutDownButton->GetY(),gameShutDownButton->GetX() + 56,gameShutDownButton->GetY() + 24 });
}
