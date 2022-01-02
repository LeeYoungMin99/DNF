#pragma once
#include "Component.h"

class StateMachineComponent;
class PlayerCommandComponent : public Component
{
private:
	using function = function<void(GameObject*, int)>;

	struct CommandNode
	{
		CommandNode() = default;

		CommandNode* nodeLeftKey = nullptr;
		CommandNode* nodeRightKey = nullptr;
		CommandNode* nodeUpKey = nullptr;
		CommandNode* nodeDownKey = nullptr;

		CommandNode* nodeSpaceKey = nullptr;
		CommandNode* nodeZKey = nullptr;

		function DoAction = nullptr;
		int stateNum = 0;
	};
public:
	using::Component::Component;
	virtual ~PlayerCommandComponent();

	virtual void Init() override;
	virtual void Update() override;

	void					CheckDoAction();
	void					CheckDash();
	void					CheckLeft();
	void					CheckRight();
	void					CheckUp();
	void					CheckDown();
	void					CheckSpace();
	void					CheckZ();
private:
	StateMachineComponent*	_statusComp = nullptr;
	float					_inputElapsedTime = 0.0f;
	CommandNode*			_noneCommand = nullptr;
	CommandNode*			_curCommand = nullptr;

	const float INPUT_TIME_LIMIT = 0.3f;
};

