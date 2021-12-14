#pragma once
#include "Character.h"

class Player : public Character
{
public:
	enum class eAttackType
	{
		None,
		NormalAttack1,
		NormalAttack2,
		NormalAttack3,
		NormalAttack4,
		NormalAttack5,
		DashAttack1,
		DashAttack2,
		JumpAttack,
	};
public:
	using Character::Character;
	virtual ~Player() noexcept = default;

	virtual void Init() override ;

	void SetAttackType(eAttackType atkType) noexcept;

	eAttackType GetAttackType() const noexcept;
private:
	eAttackType mAttackType = eAttackType::None;
};

