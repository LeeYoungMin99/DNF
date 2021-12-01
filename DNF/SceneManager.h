#pragma once
#include "Config.h"
#include "Singleton.h"

class Scene;
class SceneManager : public Singleton<SceneManager>
{
private:
	std::unordered_map<string, Scene*>	mapScenes;
	std::unordered_map<string, Scene*>	mapLoadingScenes;

public:
	virtual ~SceneManager() = default;

	static Scene* currScene;		// ���� ��� ���� ��
	static Scene* readyScene;		// �غ� ���� ��
	static Scene* loadingScene;	// �ε� ��

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddScene(string key, Scene* scene);
	void AddLoadingScene(string key, Scene* scene);

	HRESULT ChangeScene(string sceneName);
	HRESULT ChangeScene(string sceneName, string loadingSceneName);
};

