#pragma once
#include "Component.h"

enum class eState
{
	None,
	Idle,
	Walk,
	Damaged,

	AttackReady,

	Skill1,
	Skill2,
	Skill3,
	Skill4,
	Skill5,
	Skill6,
	Skill7,

	Run,
	Jump,
	JumpDownIdle,
	JumpAttack,
	DashAttack1,
	DashAttack2,
	NormalAttack1,
	NormalAttack2,
	NormalAttack3,
	NormalAttack4,
	NormalAttack5,
};

class State;
class StateMachineComponent : public Component
{
public:
	using Component::Component;
	virtual ~StateMachineComponent();

	virtual void Update() override;

	int							GetCurStateTag()						{ return _curStateTag; }

	void						AddState(State* state, eState StateTag) { _states[(int)StateTag] = state; }
	void						ChangeState(int stateTag);
	void						ChangeState(eState state);
protected:
	unordered_map<int, State*>	_states = {};
	State*						_curState = nullptr;
	int							_curStateTag = 0;
};