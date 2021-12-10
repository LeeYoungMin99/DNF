#pragma once
#include "Button.h"

class GameStartButton : public Button
{
public:
	using Button::Button;
	virtual ~GameStartButton() noexcept = default;

	virtual void Init() override;
	virtual void Update() override;
};

