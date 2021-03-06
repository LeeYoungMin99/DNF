#pragma once
#include "Component.h"

class StateMachineComponent;
class PlayerCommandComponent : public Component
{
private:
	struct CommandNode
	{
		~CommandNode();

		unordered_map<BYTE, CommandNode*> _nodes = {};

		function<void()> _doAction = nullptr;
		int _stateTag = 0;
	};
public:
	using::Component::Component;
	virtual ~PlayerCommandComponent();

	virtual void Init() override;
	virtual void Update() override;

	void									CheckCommand();
	void									CheckSkillCommand();
	PlayerCommandComponent::CommandNode*	CreateNode(BYTE keyCode);
	void									BindFunction(function<void()> doAction, int stateTag);
	void									ReadJson();
private:
	StateMachineComponent*					_stateMachineComp = nullptr;

	CommandNode*							_rootCommand = nullptr;
	CommandNode*							_curCommand = nullptr;

	float									_inputElapsedTime = 0.0f;

	const float INPUT_TIME_LIMIT = 0.3f;
};

