#include "stdafx.h"
#include "CharacterSelectScene.h"
#include "GameObject.h"
#include "Button.h"

void CharacterSelectScene::Init()
{
	// Sprite��� ���ӿ�����Ʈ ���� 
	// ��׶��� ���̾ ��׶��� �׷�����.

	Button* gameStartButton = new Button(this, L"StartButton");
	// Sprite��� ���ӿ�����Ʈ ����
	// ���� ���̾ ĳ���� ���� �׷�����.


	// Button �̶�� ���ӿ�����Ʈ ����
	// Animation ������Ʈ�� ���� �����Ҵ� ���ְ�
	// �ִϸ��̼� ����������ϰ�...
	// Button �̶�� ������Ʈ�� ���� �����Ҵ� ���ְ�
	// Ŭ�������� �ൿ ���� ������ϰ�...
	// ĳ���� �����̶��� ��ư�ΰ�? �ƴϸ� �����̶�� ���ӿ�����Ʈ�ΰ�?


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
