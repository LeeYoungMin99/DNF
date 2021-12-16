#pragma once
#include "Singleton.h"
#include "GameEntity.h"

class Player;
class PlayerStatusUI;
class UIManager : public Singleton<UIManager>, public GameEntity
{
public:
	UIManager() = default;
	virtual ~UIManager() noexcept;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void SetPlayer(Player* player) noexcept;
	float GetPlayerHP() const noexcept;
private:
	Player* mpPlayer = nullptr;

	PlayerStatusUI* mpPlayerStatus = nullptr;
};

