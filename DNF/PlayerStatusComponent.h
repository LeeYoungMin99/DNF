#pragma once
#include "Component.h"

class AnimatorComponent;
class PlayerTransformComponent;
class PositionComponent;
class PlayerStatusComponent : public Component
{
public:
	enum class ePlayerState : int
	{
		Idle,
		Walk,
		Run,
		Jump,
		JumpAttack,
		JumpDownIdle,
		NormalAttack1,
		NormalAttack2,
		NormalAttack3,
		NormalAttack4,
		NormalAttackEnd,
		DashAttackStart,
		DashAttackEnd,
		UpperSlash,
		SnakeDance,
	};
public:
	using Component::Component;
	virtual ~PlayerStatusComponent() = default;

	virtual void Init() override;
	virtual void Update() override;

	bool InputArrowKeys() { return (Input::GetButton(VK_LEFT) || Input::GetButton(VK_RIGHT) || Input::GetButton(VK_UP) || Input::GetButton(VK_DOWN)); }
	
	bool StartNormalAttack();
	bool CheckSkill_1();
	bool Jump();

	ePlayerState GetState() { return _state; }

	void						InitElapsedTime() { _elapsedStateChangeTime = 0.0f; }

	void						SetState(const ePlayerState& state) { _state = state; }
	void						SetNextState(const ePlayerState& state) { _nextState = state; }

	bool						CheckNextState();
	void						CheckCanChangeIdle();
	void						CheckCanCombo();
private:
	ePlayerState				_state = ePlayerState::Idle;
	ePlayerState				_nextState = ePlayerState::Idle;
	float						_elapsedStateChangeTime = 0.0f;
	PlayerTransformComponent*	_transformComp = nullptr;
	AnimatorComponent*			_animComp = nullptr;
	PositionComponent*			_posComp = nullptr;

	const float CAN_COMBO_INPUT = 0.25f;
};

