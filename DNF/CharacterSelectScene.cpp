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
	// Sprite��� ���ӿ�����Ʈ ���� 
	// ��׶��� �׷�����.

	// Sprite��� ���ӿ�����Ʈ ����
	// ĳ���� ���� �׷�����.

	// Button �̶�� ���ӿ�����Ʈ ����
	// Animation ������Ʈ�� ���� �����Ҵ� ���ְ�
	// �ִϸ��̼� ����������ϰ�...
	// Button �̶�� ������Ʈ�� ���� �����Ҵ� ���ְ�
	// Ŭ�������� �ൿ ���� ������ϰ�...
	// ĳ���� �����̶��� ��ư�ΰ�? �ƴϸ� �����̶�� ���ӿ�����Ʈ�ΰ�?

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
