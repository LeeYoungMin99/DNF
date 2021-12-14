#pragma once
#include "GameObject.h"

class Character : public GameObject
{
public:
	enum class eState { Idle, Walk, Run, JumpWalk, JumpRun, JumpAttack, Attack, Damaged };
	enum class eDirX { Left = -1, Right = 1 };
	enum class eDirY { Up = -1, Down = 1 };
public:
	using GameObject::GameObject;
	virtual ~Character() noexcept = default;

	eDirX GetDirX() const noexcept;
	eDirY GetDirY() const noexcept;
	eState GetState() const noexcept;
	int GetMoveSpeed() const noexcept;
	int GetZ() const noexcept;
	float GetAcceleration() const noexcept;
	float GetResistance() const noexcept;

	void AddZ(int z) noexcept;

	void SetDirX(eDirX dir) noexcept;
	void SetDirY(eDirY dir) noexcept;
	void SetMoveSpeed(int speed) noexcept;
	void SetState(eState state) noexcept;
	void SetZ(int z) noexcept;
	void SetAcceleration(float accel) noexcept;
	void SetResistance(float resist) noexcept;
protected:
	eState mState = eState::Idle;
	eDirX mDirX = eDirX::Left;
	eDirY mDirY = eDirY::Up;

	int mPosZ = 0;
	float mAcceleration = 0.0f;
	float mResistance = 0.0f;
	int mMoveSpeed = 0;
};

