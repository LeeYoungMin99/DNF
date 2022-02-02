#pragma once
#include "Component.h"

class StateMachineComponent;
class PlayerCommandComponent : public Component
{
private:
	using function = function<void(GameObject*, int)>;
	struct CommandNode
	{
		~CommandNode();

		unordered_map<BYTE, CommandNode*> nodes = {};

		function doAction = nullptr;
		int stateTag = 0;
	};
public:
	using::Component::Component;
	virtual ~PlayerCommandComponent();

	virtual void Init() override;
	virtual void Update() override;

	void					CheckCommand();
	void					CheckSkillCommand();
	void					ReadJson();
private:
	StateMachineComponent*	_stateMachineComp = nullptr;

	CommandNode*			_noneCommand = nullptr;
	CommandNode*			_curCommand = nullptr;

	float					_inputElapsedTime = 0.0f;

	const float INPUT_TIME_LIMIT = 0.3f;
};

