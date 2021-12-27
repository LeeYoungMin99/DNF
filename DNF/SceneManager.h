#pragma once
#include "Singleton.h"
#include "GameEntity.h"

class Scene;
class SceneManager : public Singleton<SceneManager>, public GameEntity
{
public:
	SceneManager() = default;
	virtual ~SceneManager();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	bool							IsSetNextScene() const;

	void							SetNextScene(const wstring& name);
	void							ChangeScene();
private:
	Scene*							_currScene = nullptr;
	Scene*							_nextScene = nullptr;
	unordered_map<wstring, Scene*>	_scenes = {};
};

