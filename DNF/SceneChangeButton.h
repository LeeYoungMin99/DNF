#pragma once
#include "GameObject.h"
#include "IButton.h"

class SceneChangeButton : public GameObject, IButton
{
public:
	SceneChangeButton(Scene* scene, const wstring& tag, wstring sceneTag);
	SceneChangeButton(GameObject* parent, const wstring& tag, wstring sceneTag);

	virtual void Init();

	virtual void OnExecuteToIdle() override { }
	virtual void OnExecuteToClick() override;
private:
	wstring _sceneTag = {};

};

