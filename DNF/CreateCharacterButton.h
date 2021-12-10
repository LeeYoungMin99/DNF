#pragma once
#include "Button.h"

class CreateCharacterButton : public Button
{
	using Button::Button;
	virtual ~CreateCharacterButton() noexcept = default;

	virtual void Init() override;
	virtual void Update() override;
};
