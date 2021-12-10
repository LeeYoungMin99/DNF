#include "stdafx.h"
#include "CharacterSelectScene.h"
#include "GameObject.h"
#include "Button.h"

void CharacterSelectScene::Init()
{
	// Sprite라는 게임오브젝트 만들어서 
	// 백그라운드 레이어에 백그라운드 그려야함.

	Button* gameStartButton = new Button(this, L"StartButton");
	// Sprite라는 게임오브젝트 만들어서
	// 슬롯 레이어에 캐릭터 슬롯 그려야함.


	// Button 이라는 게임오브젝트 만들어서
	// Animation 컴포넌트를 만들어서 동적할당 해주고
	// 애니메이션 렌더해줘야하고...
	// Button 이라는 컴포넌트를 만들어서 동적할당 해주고
	// 클릭했을때 행동 정의 해줘야하고...
	// 캐릭터 슬롯이란건 버튼인가? 아니면 슬롯이라는 게임오브젝트인가?


	Scene::Init();
}

void CharacterSelectScene::Update()
{
	Scene::Update();
}

void CharacterSelectScene::Render(HDC hdc)
{
	Scene::Render(hdc);
}
