#include "stdafx.h"
#include "framework.h"
#include "TitleScene.h"

#include "SceneManager.h"

void TitleScene::Init()
{
}

void TitleScene::Update()
{
	if (Input::GetButtonDown(VK_SPACE))
	{
		SceneManager::GetSingleton()->SetNextScene(L"CharacterSelect");
	}
}

void TitleScene::Render()
{
}

void TitleScene::Release()
{
}
