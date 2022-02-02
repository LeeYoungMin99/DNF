#include "stdafx.h"
#include "PositionComponent.h"

#include "GameObject.h"
#include "CameraManager.h"

void PositionComponent::Update()
{
	PosUpdate();

	if (_acceleration != 0.0f)
	{
		AddZ(_acceleration - _resistance);
	}

	if (_z > 0.0f)
	{
		_resistance += _acceleration * Timer::GetDeltaTime() * 2;
	}
	else
	{
		_z = 0.0f;
		_acceleration = 0.0f;
		_resistance = 0.0f;
	}
}

void PositionComponent::PosUpdate()
{
	_x = (float)(GetOwner()->GetX() + CameraManager::GetSingleton()->GetX());
	_y = (float)(GetOwner()->GetY() + CameraManager::GetSingleton()->GetY());
}
