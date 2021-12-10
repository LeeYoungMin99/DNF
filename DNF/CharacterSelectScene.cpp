#include "stdafx.h"
#include "CharacterSelectScene.h"
#include "GameObject.h"

#include "RectComponent.h"

#include "GameStartButton.h"
#include "GameShutDownButton.h"
#include "CreateCharacterButton.h"
#include "DeleteCharacterButton.h"

#include "Image.h"


void CharacterSelectScene::Init()
{
	// Sprite라는 게임오브젝트 만들어서 
	// 백그라운드 그려야함.

	// Sprite라는 게임오브젝트 만들어서
	// 캐릭터 슬롯 그려야함.

	// Button 이라는 게임오브젝트 만들어서
	// Animation 컴포넌트를 만들어서 동적할당 해주고
	// 애니메이션 렌더해줘야하고...
	// Button 이라는 컴포넌트를 만들어서 동적할당 해주고
	// 클릭했을때 행동 정의 해줘야하고...
	// 캐릭터 슬롯이란건 버튼인가? 아니면 슬롯이라는 게임오브젝트인가?

	CreateCharacterButton* createCharacterButton = new CreateCharacterButton(this, L"CreateCharacterButton");
	DeleteCharacterButton* deleteCharacterButton = new DeleteCharacterButton(this, L"DeleteCharacterStartButton");
	GameStartButton* gameStartButton = new GameStartButton(this, L"GameStartButton");
	GameShutDownButton* gameShutDownButton = new GameShutDownButton(this, L"GameShutDownButton");

	Scene::Init();

	createCharacterButton->GetComponent<RectComponent>()->SetRect({ 100,400,200,500 });
	deleteCharacterButton->GetComponent<RectComponent>()->SetRect({ 300,400,400,500 });
	gameStartButton->GetComponent<RectComponent>()->SetRect({ 500,400,600,500 });
	gameShutDownButton->GetComponent<RectComponent>()->SetRect({ 700,400,800,500 });

	createCharacterButton->SetPosition({ 100,400 });
	deleteCharacterButton->SetPosition({ 300,400 });
	gameStartButton->SetPosition({ 500,400 });
	gameShutDownButton->SetPosition({ 700,400 });

}

void CharacterSelectScene::Update()
{
	Scene::Update();
}

void CharacterSelectScene::Render()
{
	Scene::Render();
}
