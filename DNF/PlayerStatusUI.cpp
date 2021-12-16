#include "stdafx.h"
#include "PlayerStatusUI.h"

#include "UIManager.h"

#include "SpriteComponent.h"
#include "AnimatorComponent.h"
#include "RendererComponent.h"

#include "PlayerHeathBar.h"

void PlayerStatusUI::Init()
{
	AnimatorComponent* animatorComp = new AnimatorComponent(this, 101);
	animatorComp->AddSprite(new SpriteComponent(L"Image/UI/PlayerStatus.png", this), L"PlayerStatusUI");

	RendererComponent* rendererComp = new RendererComponent(animatorComp, this, 102);

	animatorComp->Play(L"PlayerStatusUI");
	animatorComp->Pause();


	SetPosition({ 533,600 });
	mpHPBar = new PlayerHealthBar(L"Image/UI/HP.png", POINT{ GetX() - 154, GetY() - 64 });
	mpMPBar = new PlayerHealthBar(L"Image/UI/MP.png", POINT{ GetX() + 138, GetY() - 64 });
}

void PlayerStatusUI::Update()
{
	GameObject::Update();

	mpHPBar->SetRemainingAmount(UIManager::GetSingleton()->GetPlayerHP());
}

void PlayerStatusUI::Render()
{
	GameObject::Render();

	mpHPBar->Render();
	mpMPBar->Render();
}

void PlayerStatusUI::Release()
{
	SAFE_RELEASE(mpHPBar);
	SAFE_RELEASE(mpMPBar);

	GameObject::Release();
}
