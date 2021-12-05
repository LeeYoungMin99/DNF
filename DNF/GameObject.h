#pragma once
#include "GameEntity.h"

class GameObject : public GameEntity
{
protected:
	enum class eAttackElementType { None, Fire, Ice, Lightning, Darkness };
	enum class eObjectType { None, Character, Monster, DestructibleMapObject, IndestructibleMapObject };
	enum class eAttackType { None, Club, Knife };

public:
	virtual ~GameObject() = default;

	virtual HRESULT Init() override { return S_OK; }
	virtual void Update() override {}
	virtual void Render(HDC hdc) override {}
	virtual void Release() override {}

	virtual void OnCollidedBody(RECT intersectionRect) {}
	virtual void OnCollidedAttack(eAttackType attackType, eAttackElementType elementType, int damage) {}

	virtual const RECT* GetBodyCollisionRect() { return &mBodyCollisionRect; }
	virtual const RECT* GetAttackCollisionRect() { return &mAttackCollisionRect; }
	virtual const eObjectType GetObjectType() { return mObjectType; }
	virtual void SetPos(float posX, float posY) { mPos.x = posX; mPos.y = posY; };
	virtual void SetBodyCollisionRect(POINTFLOAT pos, CorrectionValue correction)
	{
		mBodyCollisionRect =
		{ LONG(pos.x + GET_CAMERA_POS.x + correction.left),
			LONG(pos.y + GET_CAMERA_POS.y + correction.top),
			LONG(pos.x + GET_CAMERA_POS.x + correction.right),
			LONG(pos.y + GET_CAMERA_POS.y + correction.bottom) };
	}

protected:
	eObjectType mObjectType = eObjectType::None;
	RECT mAttackCollisionRect = {};
	RECT mBodyCollisionRect = {};
	POINTFLOAT mPos = {};

	int mStrikingPower = 0;
	int mDefensivePower = 0;
};
