#include "stdafx.h"
#include "PositionComponent.h"

#include "GameObject.h"
#include "CameraManager.h"

void PositionComponent::Update()
{
	PosUpdate();

	if (_acceleration != 0.0f)
	{
		AddZ((int)(_acceleration - _resistance));
	}

	if (_z > 0)
	{
		_resistance += _acceleration * 0.04f;
	}
	else
	{
		_z = 0;
		_acceleration = 0.0f;
		_resistance = 0.0f;
	}
}

void PositionComponent::PosUpdate()
{
	_x = _owner->GetX() + CameraManager::GetSingleton()->GetX();
	_y = _owner->GetY() + CameraManager::GetSingleton()->GetY();
}
