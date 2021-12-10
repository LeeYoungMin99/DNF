#pragma once
#include "Button.h"

class GameShutDownButton : public Button
{
public:
	using Button::Button;
	virtual ~GameShutDownButton() noexcept = default;

	virtual void Init() override;
	virtual void Update() override;
};

