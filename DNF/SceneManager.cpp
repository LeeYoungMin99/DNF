#include "stdafx.h"
#include "SceneManager.h"

#pragma region Scenes
#include "TitleScene.h"
#include "CharacterSelectScene.h"
#pragma endregion

SceneManager::~SceneManager()
{
	mpCurrScene = nullptr;
	mpNextScene = nullptr;

	for (auto& scene : mScenes)
	{
		delete scene.second;
	}

	mScenes.clear();
}

void SceneManager::Init()
{
	mScenes[L"Title"] = new TitleScene();
	mScenes[L"CharacterSelect"] = new CharacterSelectScene();
	//mScenes[L"Temp"] = new TempScene();

	mpCurrScene = mScenes[L"CharacterSelect"];
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
	//ASSERT_CRASH(_nextScene == nullptr);
	//ASSERT_CRASH(_scenes.end() != _scenes.find(name));

	mpNextScene = mScenes[name];
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