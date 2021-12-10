#pragma once
#include "Button.h"

class DeleteCharacterButton : public Button
{
public:
	using Button::Button;
	virtual ~DeleteCharacterButton() noexcept = default;

	virtual void Init() override;
	virtual void Update() override;
};

