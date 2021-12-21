#pragma once
#include "Component.h"

class RectComponent;
class HitboxComponent : public Component
{
public:
	enum class eHitBoxType { None, Body, Attack };
public:
	HitboxComponent(RectComponent* rectComp, eHitBoxType type, GameObject* owner, INT32 order = 100);
	virtual ~HitboxComponent() = default;

	virtual void Update() override;

	void SetRectSize(RECT rect) noexcept;
	void SetAttack(float strikingPower, float floatingPower, RECT rect);

	RECT GetRect() const noexcept;
private:
	eHitBoxType mType = eHitBoxType::None;
	RectComponent* mpRectComp = nullptr;

	float mStrikingPower = 0;
	float mFloatingPower = 0.0f;
};
