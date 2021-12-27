#include "stdafx.h"
#include "AttackCollisionComponent.h"

#include "Scene.h"
#include "GameObject.h"
#include "PositionComponent.h"
#include "RectColliderComponent.h"

AttackCollisionComponent::AttackCollisionComponent(RectColliderComponent* rectColliderComp, GameObject* owner, INT32 order)
	:Component(owner, order), _collider{ rectColliderComp }
{
	owner->GetScene()->AddAttackCollider(this);

	_posComp = owner->GetComponent<PositionComponent>();
}

void AttackCollisionComponent::Init()
{
	_collider->SetRectSize({ 0,0,0,0 });
	_zTop = 0;
	_zBottom = 0;
	_floatingPower = 0.0f;
	ClearHitObjs();
}

int AttackCollisionComponent::GetZTop() const
{
	return (-_posComp->GetZ()) + _zTop;
}

int AttackCollisionComponent::GetZBottom() const
{
	return (-_posComp->GetZ()) + _zBottom;
}

void AttackCollisionComponent::SetAttack(const RECT& size, float top, float bottom, float floatingPower)
{
	_collider->SetRectSize(size);
	_zTop = top;
	_zBottom = bottom;
	_floatingPower = floatingPower;
}
