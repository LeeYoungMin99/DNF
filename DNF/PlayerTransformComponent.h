#pragma once
#include "TransformComponent.h"

class StateMachineComponent;
class PlayerTransformComponent : public TransformComponent
{
public:
	using TransformComponent::TransformComponent;
	virtual ~PlayerTransformComponent()  = default;

	virtual void Init() override;
	virtual void Update() override;
private:
	StateMachineComponent*	_statusComp = nullptr;
};

