#include "stdafx.h"
#include "SceneManager.h"

#pragma region Scenes
#include "Scene.h"
#include "TitleScene.h"
#include "CharacterSelectScene.h"
#include "ElvengardFieldScene.h"
#pragma endregion

Scene* SceneManager::currScene = nullptr;
Scene* SceneManager::readyScene = nullptr;
Scene* SceneManager::loadingScene = nullptr;

DWORD CALLBACK LoadingThread(LPVOID pvParam)
{
	// ������� �ʱ�ȭ�Ѵ�.
	SceneManager::readyScene->Init();
	SceneManager::currScene = SceneManager::readyScene;

	SceneManager::loadingScene->Release();
	SceneManager::loadingScene = nullptr;
	SceneManager::readyScene = nullptr;

	return 0;
}

void SceneManager::Init()
{
	AddScene("CharacterSelectScene", new CharacterSelectScene());
	AddScene("ElvengardFieldScene", new ElvengardFieldScene());
	AddScene("TitleScene", new TitleScene());
	AddLoadingScene("TitleScene", new TitleScene());
}

void SceneManager::Release()
{
	for (auto& elem : mapScenes)
	{
		SAFE_RELEASE(elem.second);
	}

	for (auto& elem : mapLoadingScenes)
	{
		SAFE_RELEASE(elem.second);
	}

	mapScenes.clear();
	mapLoadingScenes.clear();
}

void SceneManager::Update()
{
	if (currScene)
		currScene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (currScene)
		currScene->Render(hdc);
}

void SceneManager::AddScene(string key, Scene* scene)
{
	if (scene == nullptr)	return;

	if (mapScenes.find(key) != mapScenes.end())
	{
		return;
	}

	mapScenes.emplace(key, scene);
}

void SceneManager::AddLoadingScene(string key, Scene* scene)
{
	if (scene == nullptr)	return;

	if (mapLoadingScenes.find(key) != mapLoadingScenes.end())
	{
		return;
	}

	mapLoadingScenes.emplace(key, scene);
}

HRESULT SceneManager::ChangeScene(string sceneName)
{
	auto it = mapScenes.find(sceneName);

	if (it == mapScenes.end())
		return E_FAIL;

	if (SUCCEEDED((it->second)->Init()))
	{
		if (currScene)
			currScene->Release();

		currScene = it->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT SceneManager::ChangeScene(string sceneName, string loadingSceneName)
{
	auto it = mapScenes.find(sceneName);

	if (it == mapScenes.end())
		return E_FAIL;

	// �ε��� Ȯ��
	auto itLoading = mapLoadingScenes.find(loadingSceneName);
	if (itLoading == mapLoadingScenes.end())
	{
		return ChangeScene(sceneName);
	}

	// �ε��� ���� ��
	if (SUCCEEDED((itLoading->second)->Init()))
	{
		if (currScene)
			currScene->Release();

		readyScene = it->second;
		loadingScene = itLoading->second;

		currScene = loadingScene;

		// ��Ƽ������ ó��
		DWORD loadThread;
		HANDLE hThread = CreateThread(NULL, 0,
			LoadingThread/*���� ��ų �Լ�������(�Լ��̸�)*/,
			NULL /*���� ��ų �Լ��� �� �Ű�����*/,
			0, &loadThread);

		CloseHandle(hThread);

		return S_OK;
	}

	return E_FAIL;
}
