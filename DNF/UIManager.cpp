#include "stdafx.h"
#include "UIManager.h"

#include "Player.h"
#include "PlayerStatusUI.h"

UIManager::~UIManager() noexcept
{
	SAFE_RELEASE(mpPlayerStatus);
}

void UIManager::Init()
{
	mpPlayerStatus = new PlayerStatusUI();
	mpPlayerStatus->Init();
}

void UIManager::Update()
{
	mpPlayerStatus->Update();
}

void UIManager::Render()
{
	mpPlayerStatus->Render();
}

void UIManager::Release()
{
}

void UIManager::SetPlayer(Player* player) noexcept
{
	mpPlayer = player;
}

float UIManager::GetPlayerHP() const noexcept
{
	return mpPlayer->GetHP();
}
