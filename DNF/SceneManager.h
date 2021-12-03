#pragma once
#include "Config.h"
#include "Singleton.h"

class Scene;
class SceneManager : public Singleton<SceneManager>
{
public:
	enum class eSceneTag { TitleScene, CharacterSelectScene, SeriaRoomScene, ElvengardFieldScene };

public:
	virtual ~SceneManager() = default;

	static Scene* currScene;		// 현재 출력 중인 씬
	static Scene* readyScene;		// 준비 중인 씬
	static Scene* loadingScene;	// 로딩 씬

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddScene(eSceneTag key, Scene* scene);
	void AddLoadingScene(eSceneTag key, Scene* scene);

	HRESULT ChangeScene(eSceneTag sceneName);
	HRESULT ChangeScene(eSceneTag sceneName, eSceneTag loadingSceneName);
private:
	unordered_map<eSceneTag, Scene*>	mapScenes;
	unordered_map<eSceneTag, Scene*>	mapLoadingScenes;
};

