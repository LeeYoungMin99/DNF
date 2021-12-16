#pragma once
#include "GameObject.h"

class PlayerHealthBar;
class PlayerStatusUI : public GameObject
{
public:
	PlayerStatusUI() = default;
	virtual ~PlayerStatusUI() noexcept = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
private:
	PlayerHealthBar* mpHPBar = nullptr;
	PlayerHealthBar* mpMPBar = nullptr;
};

