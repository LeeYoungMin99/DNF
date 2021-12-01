#pragma once
#include "Character.h"

class Animation;
class DemonSlayer : public Character
{
public:
	~DemonSlayer() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	eDemonSlayerState state = eDemonSlayerState::greatswordIdle;

	Animation* greatswordRightIdleMotion = nullptr;
	Animation* greatswordLeftIdleMotion = nullptr;
	Animation* greatswordRightWalkMotion = nullptr;
	Animation* greatswordLeftWalkMotion = nullptr;

	Animation* clubRightIdleMotion = nullptr;
	Animation* clubLeftIdleMotion = nullptr;
	Animation* clubRightWalkMotion = nullptr;
	Animation* clubLeftWalkMotion = nullptr;

	Animation* shortswordRightIdleMotion = nullptr;
	Animation* shortswordLeftIdleMotion = nullptr;
	Animation* shortswordRightWalkMotion = nullptr;
	Animation* shortswordLeftWalkMotion = nullptr;

	Animation* catanaRightIdleMotion = nullptr;
	Animation* catanaLeftIdleMotion = nullptr;
	Animation* catanaRightWalkMotion = nullptr;
	Animation* catanaLeftWalkMotion = nullptr;

	Animation* snakeswordRightIdleMotion = nullptr;
	Animation* snakeswordLeftIdleMotion = nullptr;
	Animation* snakeswordRightWorkMotion = nullptr;
	Animation* snakeswordLeftWorkMotion = nullptr;
};
