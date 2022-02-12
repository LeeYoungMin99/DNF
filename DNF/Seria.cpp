#include "stdafx.h"
#include "Seria.h"

#include "SpriteComponent.h"
#include "AnimatorComponent.h"
#include "Transition.h"

#include "PositionComponent.h"
#include "RectColliderComponent.h"
#include "TextComponent.h"
#include "ButtonComponent.h"

#include "SceneManager.h"
#include "NPCToolList.h"
#include "SceneChangeButton.h"

void Seria::Init()
{
	SetPosition({ 600 ,350 });
	RectColliderComponent* collisionRect = new RectColliderComponent({ -35,-150,36,0 }, this);

	AnimatorComponent* animComp = new AnimatorComponent(this);

	SpriteComponent* spriteComp = new SpriteComponent(this, 101);

	ButtonComponent* btnComp = new ButtonComponent(collisionRect, this, this);
	PositionComponent* posComp = new PositionComponent(this, 99);

	auto CanChange = [btnComp](const int& nextStateNum) {
		if ((int)(btnComp->GetState()) == nextStateNum)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	animComp->AddAnimation(L"Image/CharacterMotion/Seria/Idle.png", L"Idle");
	animComp->AddAnimation(L"Image/CharacterMotion/Seria/Hover.png", L"Hover");

	animComp->AddTransition(L"Idle", L"Hover", (int)ButtonComponent::eButtonState::Hover, CanChange);

	animComp->SetCurrAnim(L"Idle");

	NPCToolList* toolList = new NPCToolList(this, L"SeriaToolList", L"¼¼¸®¾Æ");
	SceneChangeButton* sceneChangeBtn = new SceneChangeButton(toolList, L"SeriaSceneChangeButton", L"Battle");

	GameObject::Init();
}

void Seria::OnExecuteToClick()
{
	if (GetChild(L"SeriaToolList")->GetIsActive())
	{
		GetChild(L"SeriaToolList")->Update();
	}
	else
	{
		GetChild(L"SeriaToolList")->SetIsActive(false);
		GetChild(L"SeriaToolList")->SetIsActive(true);
	}
}

