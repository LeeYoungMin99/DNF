#pragma once
#include "TransformComponent.h"

class StateMachineComponent;
class PlayerTransformComponent : public TransformComponent
{
public:
	enum class eDirY { Up, Down };
public:
	using TransformComponent::TransformComponent;
	virtual ~PlayerTransformComponent()  = default;

	virtual void Init() override;
	virtual void Update() override;

	eDirY					GetDirY() const { return _dirY; }

	void					SetDirY(const eDirY& dir) { _dirY = dir; }
private:
	eDirY					_dirY = eDirY::Up;
	StateMachineComponent*	_statusComp = nullptr;
};

