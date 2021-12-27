#pragma once
#include "Component.h"

class PositionComponent : public Component
{
public:
	using Component::Component;
	virtual ~PositionComponent() = default;

	virtual void Update() override;

	int			GetX()				const { return _x; }
	int			GetY()				const { return _y; }
	int			GetZ()				const { return _z; }
	float		GetAccelerration()	const { return _acceleration; }
	float		GetResistance()			const { return _resistance; }

	void		PosUpdate();

	void		AddZ(const int& value) { _z += value; }
	void		SetAcceleration(float accel) { _acceleration = accel; }
	void		SetResistance(float resist) { _resistance = resist; }
private:
	int			_x = 0;
	int			_y = 0;
	int			_z = 0;

	float		_acceleration = 0.0f;
	float		_resistance = 0.0f;
};

