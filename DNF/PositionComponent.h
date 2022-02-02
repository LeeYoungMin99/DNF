#pragma once
#include "Component.h"

class PositionComponent : public Component
{
public:
	using Component::Component;
	virtual ~PositionComponent() = default;

	virtual void Update() override;

	float		GetX()					const { return _x; }
	float		GetY()					const { return _y; }
	float 		GetZ()					const { return _z; }
	float		GetAccelerration()		const { return _acceleration; }
	float		GetResistance()			const { return _resistance; }

	void		PosUpdate();

	void		AddZ(const float& value) { _z += value; }
	
	void		SetZ(float value) { _z = value; }
	void		SetAcceleration(float accel) { _acceleration = accel; }
	void		SetResistance(float resist) { _resistance = resist; }
private:
	float		_x = 0;
	float		_y = 0;
	float		_z = 0;

	float		_acceleration = 0.0f;
	float		_resistance = 0.0f;
};

