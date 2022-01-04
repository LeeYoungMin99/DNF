#include "stdafx.h"
#include "BodyCollisionComponent.h"

#include "GameObject.h"
#include "Scene.h"

#include "RectColliderComponent.h"
#include "PositionComponent.h"
#include "StateMachineComponent.h"

BodyCollisionComponent::BodyCollisionComponent(RectColliderComponent* rectColliderComp, int top, int bottom, GameObject* owner, INT32 order)
	:Component(owner, order), _collider{ rectColliderComp }, _zTop{ top }, _zBottom{ bottom }
{
	owner->GetScene()->AddBodyCollider(this);

	_posComp = owner->GetComponent<PositionComponent>();
	_statusComp = owner->GetComponent<StateMachineComponent>();
}

int BodyCollisionComponent::GetZTop() const
{
	return (-_posComp->GetZ()) + _zTop;
}

int BodyCollisionComponent::GetZBottom() const
{
	return (-_posComp->GetZ()) + _zBottom;
}

void BodyCollisionComponent::OnCollided(const RECT& collisionRect)
{
	LONG width = collisionRect.right - collisionRect.left;
	LONG height = collisionRect.bottom - collisionRect.top;

	if (width < height)
	{
		if (collisionRect.left == _collider->GetRect().left)
		{
			_owner->AddX(width);
		}
		else
		{
			_owner->AddX(-width);
		}
	}
	else
	{
		if (collisionRect.top == _collider->GetRect().top)
		{
			_owner->AddY(height);
		}
		else
		{
			_owner->AddY(-height);
		}
	}

	_posComp->PosUpdate();
	_collider->Update();
}

void BodyCollisionComponent::OnCollided(float damage, float floatingPower)
{
	// 일단 고블린만 피격될 수 있게 만들었음

	if (_bIsSuperArmor)
	{
		if (floatingPower != 0)
		{
			_posComp->SetAcceleration(floatingPower);
			_posComp->SetResistance(0.0f);
		}
		else if (_posComp->GetZ() != 0)
		{
			_posComp->SetResistance(_posComp->GetAccelerration() * 0.8f);
		}

		_statusComp->ChangeState(eState::Damaged);
	}
}
