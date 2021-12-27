#pragma once
#include "Component.h"

class AnimatorComponent;
class PositionComponent;
class GoblinStatusComponent : public Component
{
public:
	enum class eGoblinState
	{
		Idle,
		Damaged,
		JumpDamaged,
		JumpDownIdle,
	};
public:
	using Component::Component;
	virtual ~GoblinStatusComponent() = default;

	virtual void Init() override;
	virtual void Update() override;

	eGoblinState	GetState() const { return _state; }

	void			SetState(const eGoblinState& state) { _state = state; }
private:
	eGoblinState		_state = eGoblinState::Idle;
	PositionComponent*	_posComp = nullptr;
	AnimatorComponent* _animComp = nullptr;
};

