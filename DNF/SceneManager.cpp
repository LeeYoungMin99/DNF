#include "stdafx.h"
#include "SceneManager.h"

#pragma region Scenes
#include "TitleScene.h"
#include "CharacterSelectScene.h"
#include "TownScene.h"
#pragma endregion

SceneManager::~SceneManager()
{
	mpCurrScene = nullptr;
	mpNextScene = nullptr;

	for (auto& scene : mpScenes)
	{
		delete scene.second;
	}

	mpScenes.clear();
}

void SceneManager::Init()
{
	mpScenes[L"Title"] = new TitleScene();
	mpScenes[L"CharacterSelect"] = new CharacterSelectScene();
	mpScenes[L"Town"] = new TownScene();

	mpCurrScene = mpScenes[L"Title"];
	mpCurrScene->Init();
}

void SceneManager::Update()
{
	if (mpCurrScene) { mpCurrScene->Update(); }
}

void SceneManager::Render()
{
	if (mpCurrScene) { mpCurrScene->Render(); }
}

void SceneManager::Release()
{
	if (mpCurrScene) { mpCurrScene->Release(); }
}

bool SceneManager::IsSetNextScene() const
{
	return mpNextScene != nullptr;
}

void SceneManager::SetNextScene(const std::wstring& name)
{
	ASSERT_CRASH(mpNextScene == nullptr);
	ASSERT_CRASH(mpScenes.end() != mpScenes.find(name));

	mpNextScene = mpScenes[name];
}

void SceneManager::ChangeScene()
{
	if (mpNextScene)
	{
		mpCurrScene->Release();

		mpCurrScene = mpNextScene;
		mpCurrScene->Init();

		mpNextScene = nullptr;
	}
}