#include "stdafx.h"
#include "PlayerCommandComponent.h"

#include "StateMachineComponent.h"

#include "GameObject.h"

PlayerCommandComponent::~PlayerCommandComponent()
{
	stack<CommandNode*> nodeStack = {};

	_curCommand = _noneCommand;
	nodeStack.push(_curCommand);

	while (nodeStack.empty() == false)
	{
		CommandNode* deleteNode = nodeStack.top();
		nodeStack.pop();

		if (deleteNode->DoAction) { deleteNode->DoAction = nullptr; }
		if (deleteNode->nodeLeftKey) { nodeStack.push(deleteNode->nodeLeftKey); }
		if (deleteNode->nodeRightKey) { nodeStack.push(deleteNode->nodeRightKey); }
		if (deleteNode->nodeUpKey) { nodeStack.push(deleteNode->nodeUpKey); }
		if (deleteNode->nodeDownKey) { nodeStack.push(deleteNode->nodeDownKey); }
		if (deleteNode->nodeSpaceKey) { nodeStack.push(deleteNode->nodeSpaceKey); }
		if (deleteNode->nodeZKey) { nodeStack.push(deleteNode->nodeZKey); }

		SAFE_DELETE(deleteNode);
	}
}

void PlayerCommandComponent::Init()
{
	_statusComp = _owner->GetComponent<StateMachineComponent>();

	auto DoAction = [](GameObject* owner, int stateNum)
	{
		owner->GetComponent<StateMachineComponent>()->ChangeState(stateNum);
	};

	_noneCommand = new CommandNode();

	_noneCommand->nodeLeftKey = new CommandNode();
	_noneCommand->nodeLeftKey->nodeLeftKey = new CommandNode();
	_noneCommand->nodeLeftKey->nodeLeftKey->DoAction = DoAction;
	_noneCommand->nodeLeftKey->nodeLeftKey->stateNum = (int)eState::Run;

	_noneCommand->nodeRightKey = new CommandNode();
	_noneCommand->nodeRightKey->nodeRightKey = new CommandNode();
	_noneCommand->nodeRightKey->nodeRightKey->DoAction = DoAction;
	_noneCommand->nodeRightKey->nodeRightKey->stateNum = (int)eState::Run;

	_noneCommand->nodeDownKey = new CommandNode();
	_noneCommand->nodeDownKey->nodeRightKey = new CommandNode();
	_noneCommand->nodeDownKey->nodeRightKey->nodeZKey = new CommandNode();
	_noneCommand->nodeDownKey->nodeRightKey->nodeZKey->DoAction = DoAction;
	_noneCommand->nodeDownKey->nodeRightKey->nodeZKey->stateNum = (int)eState::Skill2;
	_noneCommand->nodeDownKey->nodeLeftKey = new CommandNode();
	_noneCommand->nodeDownKey->nodeLeftKey->nodeZKey = new CommandNode();
	_noneCommand->nodeDownKey->nodeLeftKey->nodeZKey->DoAction = DoAction;
	_noneCommand->nodeDownKey->nodeLeftKey->nodeZKey->stateNum = (int)eState::Skill2;

	_noneCommand->nodeZKey = new CommandNode();
	_noneCommand->nodeZKey->DoAction = DoAction;
	_noneCommand->nodeZKey->stateNum = (int)eState::Skill1;

	_curCommand = _noneCommand;
}

void PlayerCommandComponent::Update()
{
	if (_curCommand != _noneCommand)
	{
		_inputElapsedTime += Timer::GetDeltaTime();

		if (_inputElapsedTime >= INPUT_TIME_LIMIT)
		{
			_curCommand = _noneCommand;
			_inputElapsedTime = 0.0f;
		}
	}

	eState state = (eState)_statusComp->GetCurStateTag();

	switch (state)
	{
	case eState::Idle:
	case eState::Walk:
	case eState::Run:
		if (Input::GetButtonDown(VK_LEFT))			{ CheckLeft();	CheckDash(); break; }
		else if (Input::GetButtonDown(VK_RIGHT))	{ CheckRight();	CheckDash(); break; }
		else if (Input::GetButtonDown(VK_UP))		{ CheckUp();	 break; }
		else if (Input::GetButtonDown(VK_DOWN))		{ CheckDown();	 break; }
		else if (Input::GetButtonDown(VK_SPACE))	{ CheckSpace();	CheckDoAction(); break; }
		else if (Input::GetButtonDown('Z'))			{ CheckZ();		CheckDoAction(); break; }
		break;
	case eState::NormalAttack1:
	case eState::NormalAttack2:
	case eState::NormalAttack3:
	case eState::NormalAttack4:
	case eState::NormalAttack5:
		if (Input::GetButtonDown(VK_LEFT))			{ CheckLeft();	break; }
		else if (Input::GetButtonDown(VK_RIGHT))	{ CheckRight();	break; }
		else if (Input::GetButtonDown(VK_UP))		{ CheckUp();	break; }
		else if (Input::GetButtonDown(VK_DOWN))		{ CheckDown();	break; }
		else if (Input::GetButtonDown(VK_SPACE))	{ CheckSpace();	CheckDoAction(); break; }
		else if (Input::GetButtonDown('Z'))			{ CheckZ();		CheckDoAction(); break; }
		break;
	}
}

void PlayerCommandComponent::CheckDoAction()
{
	if (_curCommand->DoAction != nullptr)
	{
		_curCommand->DoAction(_owner, _curCommand->stateNum);
		_curCommand = _noneCommand;
		_inputElapsedTime = 0.0f;
	}
}

void PlayerCommandComponent::CheckDash()
{
	if (_curCommand->DoAction != nullptr)	
	{
		_curCommand->DoAction(_owner, _curCommand->stateNum);
		_inputElapsedTime = 0.0f;
	}
}

void PlayerCommandComponent::CheckLeft()
{
	if (_curCommand->nodeLeftKey != nullptr) 
	{ 
		_curCommand = _curCommand->nodeLeftKey;
		_inputElapsedTime = 0.0f;
	}
}

void PlayerCommandComponent::CheckRight()
{
	if (_curCommand->nodeRightKey != nullptr)
	{
		_curCommand = _curCommand->nodeRightKey;
		_inputElapsedTime = 0.0f;
	}
}

void PlayerCommandComponent::CheckUp()
{
	if (_curCommand->nodeUpKey != nullptr) 
	{
		_curCommand = _curCommand->nodeUpKey; 
		_inputElapsedTime = 0.0f;
	}
}

void PlayerCommandComponent::CheckDown()
{
	if (_curCommand->nodeDownKey != nullptr) 
	{ 
		_curCommand = _curCommand->nodeDownKey; 
		_inputElapsedTime = 0.0f;
	}
}

void PlayerCommandComponent::CheckSpace()
{
	if (_curCommand->nodeSpaceKey != nullptr) 
	{
		_curCommand = _curCommand->nodeSpaceKey; 
		_inputElapsedTime = 0.0f;
	}
}

void PlayerCommandComponent::CheckZ()
{
	if (_curCommand->nodeZKey != nullptr) 
	{ 
		_curCommand = _curCommand->nodeZKey; 
		_inputElapsedTime = 0.0f;
	}
}
