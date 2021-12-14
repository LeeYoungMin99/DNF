#pragma once
#include "Component.h"

class PlayerAttackComponent : public Component
{
public:
	using Component::Component;
	virtual ~PlayerAttackComponent() noexcept = default;

	virtual void Update() override;

	void SetAnimation(const wchar_t* tag);
};

