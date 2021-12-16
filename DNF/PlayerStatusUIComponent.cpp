#include "stdafx.h"
#include "PlayerStatusUIComponent.h"

#include "SpriteComponent.h"
#include "AnimatorComponent.h"
#include "RendererComponent.h"

#include "ImageManager.h"
#include "Image.h"
#include "PlayerHeathBar.h"
#include "Player.h"

void PlayerStatusUIComponent::Init()
{
	mpPlayerStatusUI = ImageManager::GetSingleton()->FindImage(L"Image/UI/PlayerStatus.png");
	mpHPBar = new PlayerHealthBar(L"Image/UI/HP.png", POINT{ 379,536 });
	mpMPBar = new PlayerHealthBar(L"Image/UI/MP.png", POINT{ 671,536 });
}

void PlayerStatusUIComponent::Update()
{
	Player* pPlayer = (Player*)mpOwner;

	mpHPBar->SetRemainingAmount(pPlayer->GetHP());
	mpMPBar->SetRemainingAmount(pPlayer->GetMP());
}

void PlayerStatusUIComponent::Render()
{
	mpPlayerStatusUI->Render(367, 525);
	mpHPBar->Render();
	mpMPBar->Render();
}

void PlayerStatusUIComponent::Release()
{
	SAFE_RELEASE(mpHPBar);
	SAFE_RELEASE(mpMPBar);
}
