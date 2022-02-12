#include "stdafx.h"
#include "SceneManager.h"

#pragma region Scenes
#include "TownScene.h"
#include "BattleScene.h"
#pragma endregion

SceneManager::~SceneManager()
{
	_currScene = nullptr;
	_nextScene = nullptr;

	for (auto& scene : _scenes)
	{
		SAFE_RELEASE(scene.second);
	}

	_scenes.clear();
}

void SceneManager::Init()
{
	_scenes[L"Town"] = new TownScene();
	_scenes[L"Battle"] = new BattleScene();

	_currScene = _scenes[L"Town"];
	_currScene->Init();
}

void SceneManager::Update()
{
	if (_currScene) { _currScene->Update(); }
}

void SceneManager::Render()
{
	if (_currScene) { _currScene->Render(); }
}

void SceneManager::Release()
{
	if (_currScene) { _currScene->Release(); }
}

bool SceneManager::IsSetNextScene() const
{
	return _nextScene != nullptr;
}

void SceneManager::SetNextScene(const std::wstring& name)
{
	ASSERT_CRASH(_nextScene == nullptr);
	ASSERT_CRASH(_scenes.end() != _scenes.find(name));

	_nextScene = _scenes[name];
}

void SceneManager::ChangeScene()
{
	if (_nextScene)
	{
		_currScene->Release();

		_currScene = _nextScene;
		_currScene->Init();

		_nextScene = nullptr;
	}
}