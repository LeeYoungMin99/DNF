#include "stdafx.h"
#include "PlayerCommandComponent.h"

#include "PlayerStatusComponent.h"

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
	_statusComp = _owner->GetComponent<PlayerStatusComponent>();

	auto DoAction = [](GameObject* owner, int stateNum)
	{
		owner->GetComponent<PlayerStatusComponent>()->SetState((PlayerStatusComponent::ePlayerState)stateNum);
	};

	_noneCommand = new CommandNode();

	_noneCommand->nodeLeftKey = new CommandNode();
	_noneCommand->nodeLeftKey->nodeLeftKey = new CommandNode();
	_noneCommand->nodeLeftKey->nodeLeftKey->DoAction = DoAction;
	_noneCommand->nodeLeftKey->nodeLeftKey->stateNum = (int)PlayerStatusComponent::ePlayerState::Run;

	_noneCommand->nodeRightKey = new CommandNode();
	_noneCommand->nodeRightKey->nodeRightKey = new CommandNode();
	_noneCommand->nodeRightKey->nodeRightKey->DoAction = DoAction;
	_noneCommand->nodeRightKey->nodeRightKey->stateNum = (int)PlayerStatusComponent::ePlayerState::Run;

	_noneCommand->nodeDownKey = new CommandNode();
	_noneCommand->nodeDownKey->nodeRightKey = new CommandNode();
	_noneCommand->nodeDownKey->nodeRightKey->nodeZKey = new CommandNode();
	_noneCommand->nodeDownKey->nodeRightKey->nodeZKey->DoAction = DoAction;
	_noneCommand->nodeDownKey->nodeRightKey->nodeZKey->stateNum = (int)PlayerStatusComponent::ePlayerState::SnakeDance;
	_noneCommand->nodeDownKey->nodeLeftKey = new CommandNode();
	_noneCommand->nodeDownKey->nodeLeftKey->nodeZKey = new CommandNode();
	_noneCommand->nodeDownKey->nodeLeftKey->nodeZKey->DoAction = DoAction;
	_noneCommand->nodeDownKey->nodeLeftKey->nodeZKey->stateNum = (int)PlayerStatusComponent::ePlayerState::SnakeDance;

	_noneCommand->nodeZKey = new CommandNode();
	_noneCommand->nodeZKey->DoAction = DoAction;
	_noneCommand->nodeZKey->stateNum = (int)PlayerStatusComponent::ePlayerState::UpperSlash;

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

	using _state = PlayerStatusComponent::ePlayerState;
	switch (_statusComp->GetState())
	{
	case _state::Idle:
	case _state::Walk:
	case _state::Run:
		if (Input::GetButtonDown(VK_LEFT))			{ CheckLeft();	CanAction(); break; }
		else if (Input::GetButtonDown(VK_RIGHT))	{ CheckRight();	CanAction(); break; }
		else if (Input::GetButtonDown(VK_UP))		{ CheckUp();	CanAction(); break; }
		else if (Input::GetButtonDown(VK_DOWN))		{ CheckDown();	CanAction(); break; }
		else if (Input::GetButtonDown(VK_SPACE))	{ CheckSpace();	CanAction(); break; }
		else if (Input::GetButtonDown('Z'))			{ CheckZ();		CanAction(); break; }
		break;
		break;
	case _state::NormalAttack1:
	case _state::NormalAttack2:
	case _state::NormalAttack3:
	case _state::NormalAttack4:
	case _state::NormalAttackEnd:
		if (Input::GetButtonDown(VK_LEFT))			{ CheckLeft();	break; }
		else if (Input::GetButtonDown(VK_RIGHT))	{ CheckRight();	break; }
		else if (Input::GetButtonDown(VK_UP))		{ CheckUp();	break; }
		else if (Input::GetButtonDown(VK_DOWN))		{ CheckDown();	break; }
		else if (Input::GetButtonDown(VK_SPACE))	{ CheckSpace();	CanAction(); break; }
		else if (Input::GetButtonDown('Z'))			{ CheckZ();		CanAction(); break; }
		break;
	}
}

void PlayerCommandComponent::CanAction()
{
	if (_curCommand->DoAction != nullptr)
	{
		_curCommand->DoAction(_owner, _curCommand->stateNum);
		_curCommand = _noneCommand;
		_inputElapsedTime = 0.0f;
	}
}

void PlayerCommandComponent::CheckLeft()
{
	if (_curCommand->nodeLeftKey != nullptr) { _curCommand = _curCommand->nodeLeftKey; }
}

void PlayerCommandComponent::CheckRight()
{
	if (_curCommand->nodeRightKey != nullptr) { _curCommand = _curCommand->nodeRightKey; }
}

void PlayerCommandComponent::CheckUp()
{
	if (_curCommand->nodeUpKey != nullptr) { _curCommand = _curCommand->nodeUpKey; }
}

void PlayerCommandComponent::CheckDown()
{
	if (_curCommand->nodeDownKey != nullptr) { _curCommand = _curCommand->nodeDownKey; }
}

void PlayerCommandComponent::CheckSpace()
{
	if (_curCommand->nodeSpaceKey != nullptr) { _curCommand = _curCommand->nodeSpaceKey; }
}

void PlayerCommandComponent::CheckZ()
{
	if (_curCommand->nodeZKey != nullptr) { _curCommand = _curCommand->nodeZKey; }
}
