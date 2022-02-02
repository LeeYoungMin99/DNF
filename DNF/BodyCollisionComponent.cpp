#include "stdafx.h"
#include "BodyCollisionComponent.h"

#include "GameObject.h"
#include "Scene.h"

#include "RectColliderComponent.h"
#include "PositionComponent.h"
#include "StateMachineComponent.h"
#include "State.h"

BodyCollisionComponent::BodyCollisionComponent(RectColliderComponent* rectColliderComp, float top, float bottom, GameObject* owner, INT32 order)
	:Component(owner, order), _collider{ rectColliderComp }, _zTop{ top }, _zBottom{ bottom }
{
	owner->GetScene()->AddBodyCollider(this);

	_posComp = owner->GetComponent<PositionComponent>();
	_stateMachineComp = owner->GetComponent<StateMachineComponent>();
}

float BodyCollisionComponent::GetZTop() const
{
	return _posComp->GetZ() + _zTop;
}

float BodyCollisionComponent::GetZBottom() const
{
	return _posComp->GetZ() + _zBottom;
}

void BodyCollisionComponent::OnCollided(const RECT& collisionRect)
{
	LONG width = collisionRect.right - collisionRect.left;
	LONG height = collisionRect.bottom - collisionRect.top;

	if (width < height)
	{
		if (collisionRect.left == _collider->GetRect().left)
		{
			GetOwner()->AddX(width);
		}
		else
		{
			GetOwner()->AddX(-width);
		}
	}
	else
	{
		if (collisionRect.top == _collider->GetRect().top)
		{
			GetOwner()->AddY(height);
		}
		else
		{
			GetOwner()->AddY(-height);
		}
	}

	_posComp->PosUpdate();
	_collider->Update();
}

void BodyCollisionComponent::OnCollided(float damage, float floatingPower, float resistance)
{
	if (false == _bIsSuperArmor)
	{
		if (floatingPower != 0)
		{
			_posComp->SetAcceleration(floatingPower);
			_posComp->SetResistance(resistance);
		}
		else if (_posComp->GetZ() != 0)
		{
			_posComp->SetResistance(_posComp->GetAccelerration() * 0.7f);
		}
		else if ((eState)_stateMachineComp->GetCurStateTag() == eState::Damaged)
		{
			if (((Damaged*)(_stateMachineComp->GetCurState()))->GetIsFloatOnce())
			{
				_posComp->SetAcceleration(20.0f);
				_posComp->SetResistance(_posComp->GetAccelerration() * 0.92f);
			}
		}

		if ((eState)_stateMachineComp->GetCurStateTag() != eState::Damaged)
		{
			_stateMachineComp->ChangeState(eState::Damaged);
		}
	}
}
