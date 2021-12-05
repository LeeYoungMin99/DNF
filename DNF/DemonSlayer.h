#pragma once
#include "Character.h"

class Animation;
class DemonSlayer : public Character
{
	enum class eWeaponType { Greatsword, Club, Shortsword, Catana, Snakesword };
	enum class eDemonSlayerState
	{
		Idle,
		Walk,
		Run,
		Damage,
		Jump,
		BasickAttak1,
		BasickAttak2,
		BasickAttak3,
		BasickAttak4,
	};

public:
	~DemonSlayer() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	void UpdateIdle();
	void UpdateWalk();

	virtual void OnCollidedBody(RECT intersectionRect) override;
	virtual void OnCollidedAttack(eAttackType attackType, eAttackElementType elementType, int damage) override;


private:
	eDemonSlayerState mState = eDemonSlayerState::Idle;
	eWeaponType mWeaponType = eWeaponType::Greatsword;

	Animation* mpMotion[2][5][256] = {};
};
