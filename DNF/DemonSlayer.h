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
	void SetAnimation(int dir, int weaponType, int state, AnimationData data);
	void UpdateIdleState(int dir);
	void UpdateWalkState(int dir);
	void RenderState(HDC hdc, int dir,int state, POINTFLOAT pos);
private:
#define DIR (int)DemonSlayer::eDir
#define WEAPON_TYPE (int)DemonSlayer::eWeaponType
#define STATE (int)DemonSlayer::eDemonSlayerState
	enum class eDir { Left, Right };
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

	eDemonSlayerState mState = eDemonSlayerState::Idle;
	eWeaponType mWeaponType = eWeaponType::Greatsword;

	Animation* mpMotion[2][5][256] = {};
};
