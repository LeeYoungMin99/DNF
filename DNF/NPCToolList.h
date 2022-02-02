#pragma once
#include "GameObject.h"
#include "IButton.h"

class NPCToolList : public GameObject, IButton
{
public:
	NPCToolList(GameObject* parent, const wstring& tag, const wchar_t* name);
	virtual ~NPCToolList() = default;

	virtual void Init() override;

private:
	virtual void OnEnable() override;

	virtual void OnExecuteToIdle() override;
	virtual void OnExecuteToClick() override { }
private:
	const wchar_t* _name = {};

};

