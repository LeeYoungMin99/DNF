#pragma once
#include "State.h"

class PlayerState : public State
{
public:
	using State::State;
	virtual ~PlayerState() = default;

	bool InputPlayerAttackKey() { return Input::GetButtonDown(PLAYER_ATTACK_KEY); }
	bool InputPlayerJumpKey()	{ return Input::GetButtonDown(PLAYER_JUMP_KEY); }
	bool InputPlayerMoveKey()	{ return (Input::GetButton(PLAYER_LEFT_MOVE_KEY) || Input::GetButton(PLAYER_RIGHT_MOVE_KEY) || Input::GetButton(PLAYER_UP_MOVE_KEY) || Input::GetButton(PLAYER_DOWN_MOVE_KEY)); }
protected:
	const char PLAYER_ATTACK_KEY = 'X';
	const char PLAYER_JUMP_KEY = 'C';

	const char PLAYER_LEFT_MOVE_KEY	 = VK_LEFT;
	const char PLAYER_RIGHT_MOVE_KEY = VK_RIGHT;
	const char PLAYER_UP_MOVE_KEY	 = VK_UP;
	const char PLAYER_DOWN_MOVE_KEY	 = VK_DOWN;

	const char PLAYER_SKILL_QUICK_SLOT_1_KEY  = 'A';
	const char PLAYER_SKILL_QUICK_SLOT_2_KEY  = 'S';
	const char PLAYER_SKILL_QUICK_SLOT_3_KEY  = 'D';
	const char PLAYER_SKILL_QUICK_SLOT_4_KEY  = 'F';
	const char PLAYER_SKILL_QUICK_SLOT_5_KEY  = 'G';
	const char PLAYER_SKILL_QUICK_SLOT_6_KEY  = 'H';
	const char PLAYER_SKILL_QUICK_SLOT_7_KEY  = 'J';
											  
	const char PLAYER_SKILL_QUICK_SLOT_8_KEY  = 'Q';
	const char PLAYER_SKILL_QUICK_SLOT_9_KEY  = 'W';
	const char PLAYER_SKILL_QUICK_SLOT_10_KEY = 'E';
	const char PLAYER_SKILL_QUICK_SLOT_11_KEY = 'R';
	const char PLAYER_SKILL_QUICK_SLOT_12_KEY = 'T';
	const char PLAYER_SKILL_QUICK_SLOT_13_KEY = 'Y';
	const char PLAYER_SKILL_QUICK_SLOT_14_KEY = 'U';
};

class AnimatorComponent;
class PlayerAction : public PlayerState
{
public:
	PlayerAction(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~PlayerAction() = default;

	virtual void Update() override;
protected:
	bool EndAnimation();
protected:
	AnimatorComponent* _animComp = nullptr;
};

class PlayerIdle : public PlayerState
{
public:
	using PlayerState::PlayerState;
	virtual ~PlayerIdle() = default;

	virtual void Update() override;
};

class PlayerWalk : public PlayerState
{
public:
	using PlayerState::PlayerState;
	virtual ~PlayerWalk() = default;

	virtual void Update() override;
};

class TransformComponent;
class PlayerRun : public PlayerState
{
public:
	PlayerRun(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~PlayerRun() = default;

	virtual void Update() override;
private:
	TransformComponent* _transformComp = nullptr;
};

class PositionComponent;
class PlayerJump : public PlayerState
{
public:
	PlayerJump(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~PlayerJump() = default;

	virtual void Init() override;
	virtual void Update() override;
private:
	PositionComponent* _posComp = nullptr;
};

class PositionComponent;
class PlayerJumpAttack : public PlayerState
{
public:
	PlayerJumpAttack(StateMachineComponent* stateMachine, GameObject* owner);
	virtual ~PlayerJumpAttack() = default;

	virtual void Update() override;
private:
	PositionComponent* _posComp = nullptr;
};

class PlayerAttack : public PlayerAction
{
	using PlayerAction::PlayerAction;
	virtual ~PlayerAttack() = default;

	virtual void Init() override;
	virtual void Update() override;

	bool CheckCanCombo();
private:
	float _elapsedTime = 0.0f;
	bool _bInputCombo = false;

	float CAN_INPUT_ELAPSED_TIME = 0.20f;
	const int NEXT_STATE = 1;
};
