#pragma once
#include "Component.h"

class PlayerMovementComponent : public Component
{
public:
	using Component::Component;
	virtual ~PlayerMovementComponent() noexcept = default;

	virtual void Update() override;

	void SetAnimation(const wchar_t* tag);
	void ChangeZ();
	void Move(int state, int dirX, int dirY, float deltaTime) noexcept;
	void InitFlightTime() noexcept;
	void SetFlightTime(float value) noexcept;
private:
	float mInputTime = 0.0f;
	float mFlightTime = 0.0f;
	int mPrevKey = 0;
};

