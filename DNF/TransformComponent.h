#pragma once
#include "Component.h"

class TransformComponent : public Component
{
public:
	enum class eDirX
	{
		Left = -1,
		Right = 1
	};

	enum class eDirY
	{
		Up = -1,
		Down = 1
	};

public:
	using Component::Component;
	virtual ~TransformComponent() = default;

	void			SetDirX(const eDirX& dir) { _dirX = dir; }
	void			SetDirY(const eDirY& dir) { _dirY = dir; }

	eDirX			GetDirX() const { return _dirX; }
	eDirY			GetDirY() const { return _dirY; }

	void			ChangeDirY() {
		if (_dirY == eDirY::Up) { _dirY = eDirY::Down; }
		else { _dirY = eDirY::Up; }
	}
protected:
	eDirX			_dirX = eDirX::Left;
	eDirY			_dirY = eDirY::Up;
};
