#pragma once
#include "Character.h"

class Animation;
class Seria : public Character
{
public:
	enum class eSeriaState { Idle, Hover };
public:
	virtual ~Seria() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	Animation* mpIdleMotion = nullptr;
	Animation* mpHoverMotion = nullptr;

	eSeriaState mState = eSeriaState::Idle;

	const int BODY_SIZE_X = 58;
	const int BODY_SIZE_Y = 116;

	const int IMAGE_SIZE_X = 116;
	const int IMAGE_SIZE_Y = 232;
	const int CORRECTION_IMAGE_POS_Y = 0;
	const int BODY_COLLISION_LEFT = -BODY_SIZE_X;
	const int BODY_COLLISION_TOP = -BODY_SIZE_Y;
	const int BODY_COLLISION_RIGHT = BODY_SIZE_X;
	const int BODY_COLLISION_BOTTOM = BODY_SIZE_Y;
};