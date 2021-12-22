#pragma once
#include "Character.h"

class HitboxComponent;
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
		SnakeDance,
	};
public:
	using Character::Character;
	virtual ~Player() noexcept = default;

	virtual void Init() override;

	void InitAttackHitbox();

	void SetAttackType(eAttackType atkType) noexcept;
	void SetAttackHitbox(float strikingPower, float floatingPower, RECT rect) noexcept;

	void AddHP(float value) noexcept;
	void AddMP(float value) noexcept;

	eAttackType GetAttackType() const noexcept;
	float GetHP() const noexcept;
	float GetMP() const noexcept;

	virtual void OnBodyCollided(RECT collisionSize) override;
	virtual void OnAttackCollided(float strikingPower, float floatingPower) override;

private:
	eAttackType mAttackType = eAttackType::None;
	float mHP = 100.0f;
	float mMP = 100.0f;

	HitboxComponent* mpAttackHitBoxComp = nullptr;
	HitboxComponent* mpBodyHitBoxComp = nullptr;
};

