#include "stdafx.h"
#include "PlayerCommandComponent.h"

#include "StateMachineComponent.h"

#include "GameObject.h"
#include "State.h"

PlayerCommandComponent::~PlayerCommandComponent()
{
	_curCommand = _rootCommand;
	SAFE_DELETE(_rootCommand);
}

void PlayerCommandComponent::Init()
{
	_stateMachineComp = GetOwner()->GetComponent<StateMachineComponent>();

	_rootCommand = new CommandNode();

	ReadJson();

	_curCommand = _rootCommand;
}

void PlayerCommandComponent::Update()
{
	if (_curCommand != _rootCommand)
	{
		_inputElapsedTime += Timer::GetDeltaTime();

		if (_inputElapsedTime >= INPUT_TIME_LIMIT)
		{
			_curCommand = _rootCommand;
			_inputElapsedTime = 0.0f;
		}
	}

	eState state = (eState)_stateMachineComp->GetCurStateTag();

	switch (state)
	{
	case eState::Idle:
	case eState::Walk:
	case eState::Run:
		CheckCommand();
		break;
	case eState::NormalAttack1:
	case eState::NormalAttack2:
	case eState::NormalAttack3:
	case eState::NormalAttack4:
	case eState::NormalAttack5:
		CheckSkillCommand();
		break;
	}
}

void PlayerCommandComponent::CheckCommand()
{
	for (const auto& node : _curCommand->_nodes)
	{
		CommandNode* commandNode = node.second;
		BYTE keyCode = node.first;

		if (Input::GetButtonDown(keyCode))
		{
			_curCommand = commandNode;

			_inputElapsedTime = 0.0f;

			if (nullptr != _curCommand->_doAction)
			{
				_curCommand->_doAction();
				_curCommand = _rootCommand;
			}

			break;
		}
	}
}

void PlayerCommandComponent::CheckSkillCommand()
{
	for (auto node : _curCommand->_nodes)
	{
		CommandNode* commandNode = node.second;
		BYTE keyCode = node.first;

		if (Input::GetButtonDown(keyCode))
		{
			_curCommand = commandNode;

			_inputElapsedTime = 0.0f;

			if (_curCommand->_doAction && (keyCode != VK_LEFT && keyCode != VK_RIGHT && keyCode != VK_DOWN && keyCode != VK_UP))
			{
				_curCommand->_doAction();
				_curCommand = _rootCommand;
			}

			break;
		}
	}
}

PlayerCommandComponent::CommandNode* PlayerCommandComponent::CreateNode(BYTE keyCode)
{
	if (nullptr == _curCommand->_nodes[keyCode])
	{
		_curCommand->_nodes[keyCode] = new CommandNode();
	}

	return _curCommand->_nodes[keyCode];
}

void PlayerCommandComponent::BindFunction(function<void()> doAction,int stateTag)
{
	_curCommand->_stateTag = stateTag;
	_curCommand->_doAction = doAction;
}

void PlayerCommandComponent::ReadJson()
{
	char path[MAX_PATH];
	string jsonPath;

	if (GetCurrentDirectoryA(128, path) > 0)
	{
		jsonPath = path + string{ "\\JSON_DATA.json" };
	}
	else
	{
		cout << "Parse Failed." << endl;
		return;
	}
	
	ifstream json_dir(jsonPath);
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	Json::Value value; 
	JSONCPP_STRING errs;
	bool ok = parseFromStream(builder, json_dir, &value, &errs);
	if (ok == true)
	{
		StateMachineComponent* stateMachineComp = GetOwner()->GetComponent<StateMachineComponent>();

		auto doAction = [this,stateMachineComp]()
		{
			stateMachineComp->ChangeState(this->_curCommand->_stateTag);
		};

		int index = 0;
		unordered_map<string, int> stringToEnum = {};
		stringToEnum["Run"] = 12;
		stringToEnum["승천검"] = 5;
		stringToEnum["사복검-무"] = 6;

		const auto keyName = value.getMemberNames();

		for (const auto& skill : value)
		{
			_curCommand = _rootCommand;

			queue<BYTE> commandQueue = {};

			BYTE keyCode = 0;

			for (const auto& command : skill["Command"])
			{
				string key = command.asString();

				if (key.size() == 1)			{ keyCode = key[0]; }
				else
				{
					if ("Left" == key)			{ keyCode = VK_LEFT; }
					else if ("Up" == key)		{ keyCode = VK_UP; }
					else if ("Right" == key)	{ keyCode = VK_RIGHT; }
					else if ("Down" == key)		{ keyCode = VK_DOWN; }
					else
					{
						static_assert(true, "Unusable Key Value");
					}
				}

				_curCommand = CreateNode(keyCode);

				commandQueue.emplace(keyCode);
			}

			BindFunction(doAction,stringToEnum[keyName[index]]);

			_curCommand = _rootCommand;

			while (false == commandQueue.empty())
			{
				BYTE front = commandQueue.front();
				commandQueue.pop();

				if (front == VK_LEFT)		{ keyCode = VK_RIGHT; }
				else if (front == VK_RIGHT) { keyCode = VK_LEFT; }
				else						{ keyCode = front; }

				_curCommand = CreateNode(keyCode);
			}

			BindFunction(doAction, stringToEnum[keyName[index]]);
			
			++index;
		}
	}
	else
	{
		cout << "Parse Failed." << endl;
	}
}

PlayerCommandComponent::CommandNode::~CommandNode()
{
	for (auto& node : _nodes)
	{
		node.second->_doAction = nullptr;
		SAFE_DELETE(node.second);
	}

	_nodes.clear();
}
