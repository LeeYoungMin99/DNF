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
public:
	using Component::Component;
	virtual ~TransformComponent() = default;

	void			SetDirX(const eDirX& dir) { _dirX = dir; }

	eDirX			GetDirX() const { return _dirX; }
protected:
	eDirX			_dirX = eDirX::Left;
};
