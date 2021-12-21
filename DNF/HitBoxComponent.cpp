#include "stdafx.h"
#include "HitBoxComponent.h"

#include "RectComponent.h"
#include "GameObject.h"

HitboxComponent::HitboxComponent(RectComponent* rectComp, eHitBoxType type, GameObject* owner, INT32 order)
	:Component(owner, order)
{
	mpRectComp = rectComp;
	mType = type;
}

void HitboxComponent::Update()
{
	POINT pos = mpOwner->GetPosition();
}

void HitboxComponent::SetRectSize(RECT rect) noexcept
{
	mpRectComp->SetRectSize(rect);
}

void HitboxComponent::SetAttack(float strikingPower, float floatingPower, RECT rect)
{
	mStrikingPower = strikingPower;
	mFloatingPower = floatingPower;
	SetRectSize(rect);
}

RECT HitboxComponent::GetRect() const noexcept
{
	return mpRectComp->GetRect();
}
