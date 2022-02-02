#include "stdafx.h"
#include "PlayerCommandComponent.h"

#include "StateMachineComponent.h"

#include "GameObject.h"
#include "State.h"

PlayerCommandComponent::~PlayerCommandComponent()
{
	//stack<CommandNode*> nodeStack = {};

	_curCommand = _noneCommand;
	SAFE_DELETE(_noneCommand);
	//nodeStack.push(_noneCommand);

	//while (nodeStack.empty() == false)
	//{
	//	CommandNode* deleteNode = nodeStack.top();
	//	nodeStack.pop();
	//
	//	if (deleteNode->doAction) { deleteNode->doAction = nullptr; }
	//
	//	for (auto node : deleteNode->nodes)
	//	{
	//		nodeStack.push(node.second);
	//	}
	//
	//	SAFE_DELETE(deleteNode);
	//}
}

void PlayerCommandComponent::Init()
{

	_stateMachineComp = GetOwner()->GetComponent<StateMachineComponent>();

	auto doAction = [](GameObject* owner, int stateTag)
	{
		owner->GetComponent<StateMachineComponent>()->ChangeState(stateTag);
	};

	_noneCommand = new CommandNode();

	ReadJson();

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
	for (const auto& node : _curCommand->nodes)
	{
		CommandNode* commandNode = node.second;
		BYTE keyCode = node.first;

		if (Input::GetButtonDown(node.first))
		{
			_curCommand = commandNode;

			_inputElapsedTime = 0.0f;

			if (_curCommand->doAction)
			{
				_curCommand->doAction(GetOwner(), _curCommand->stateTag);
				_curCommand = _noneCommand;
			}

			break;
		}
	}
}

void PlayerCommandComponent::CheckSkillCommand()
{
	for (auto node : _curCommand->nodes)
	{
		CommandNode* commandNode = node.second;
		BYTE keyCode = node.first;

		if (Input::GetButtonDown(node.first))
		{
			_curCommand = commandNode;

			_inputElapsedTime = 0.0f;

			if (_curCommand->doAction && (keyCode != VK_LEFT && keyCode != VK_RIGHT && keyCode != VK_DOWN && keyCode != VK_UP))
			{
				_curCommand->doAction(GetOwner(), _curCommand->stateTag);
				_curCommand = _noneCommand;
			}

			break;
		}
	}
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

	auto doAction = [](GameObject* owner, int stateTag)
	{
		owner->GetComponent<StateMachineComponent>()->ChangeState(stateTag);
	};

	ifstream json_dir(jsonPath);
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	Json::Value value; JSONCPP_STRING errs;
	bool ok = parseFromStream(builder, json_dir, &value, &errs);
	if (ok == true)
	{
		for (const auto& skill : value)
		{
			_curCommand = _noneCommand;

			for (const auto& command : skill["Command"])
			{
				string key = command.asString();

				CommandNode* newCommand;

				if (key.size() == 1)
				{
					BYTE keyCode = key[0];

					if (_curCommand->nodes[keyCode])
					{
						newCommand = _curCommand->nodes[keyCode];
					}
					else
					{
						newCommand = new CommandNode();
						_curCommand->nodes[keyCode] = newCommand;
					}
				}
				else
				{
					if ("Left" == key)
					{
						if (_curCommand->nodes[VK_LEFT])
						{
							newCommand = _curCommand->nodes[VK_LEFT];
						}
						else
						{
							newCommand = new CommandNode();
							_curCommand->nodes[VK_LEFT] = newCommand;
						}
					}
					else if ("Up" == key)
					{
						if (_curCommand->nodes[VK_UP])
						{
							newCommand = _curCommand->nodes[VK_UP];
						}
						else
						{
							newCommand = new CommandNode();
							_curCommand->nodes[VK_UP] = newCommand;
						}
					}
					else if ("Right" == key)
					{
						if (_curCommand->nodes[VK_RIGHT])
						{
							newCommand = _curCommand->nodes[VK_RIGHT];
						}
						else
						{
							newCommand = new CommandNode();
							_curCommand->nodes[VK_RIGHT] = newCommand;
						}
					}
					else if ("Down" == key)
					{
						if (_curCommand->nodes[VK_DOWN])
						{
							newCommand = _curCommand->nodes[VK_DOWN];
						}
						else
						{
							newCommand = new CommandNode();
							_curCommand->nodes[VK_DOWN] = newCommand;
						}
					}
					else
					{
						static_assert(true, "Unusable Key Value");
					}
				}

				_curCommand = newCommand;
			}

			_curCommand->doAction = doAction;
			_curCommand->stateTag = skill["StateTag"].asInt();
		}
	}
	else
	{
		cout << "Parse Failed." << endl;
	}
}

PlayerCommandComponent::CommandNode::~CommandNode()
{
	for (auto& node : nodes)
	{
		node.second->doAction = nullptr;
		SAFE_DELETE(node.second);
	}

	nodes.clear();
}
