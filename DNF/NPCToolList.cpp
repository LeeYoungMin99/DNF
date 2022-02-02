#include "stdafx.h"
#include "NPCToolList.h"

#include "SpriteComponent.h"
#include "AnimatorComponent.h"
#include "Transition.h"

#include "ButtonComponent.h"
#include "PositionComponent.h"
#include "RectColliderComponent.h"
#include "TextComponent.h"

NPCToolList::NPCToolList(GameObject* parent, const wstring& tag, const wchar_t* name)
	:GameObject(parent, tag), _name{ name } { }

void NPCToolList::Init()
{
	RectColliderComponent* collisionRect = new RectColliderComponent({ 0,0,0,0 }, this);

	TextComponent* textComp = new TextComponent(_name, L"¸ð¸®½º9", 18, { 255,255,255 }, this, 102);
	textComp->SetRect({ 0, 0, 100,21 });

	ButtonComponent* btnComp = new ButtonComponent(collisionRect, this, this);

	AnimatorComponent* animComp = new AnimatorComponent(this);

	SpriteComponent* spriteComp = new SpriteComponent(this, 101);

	PositionComponent* posComp = new PositionComponent(this, 99);

	animComp->AddAnimation(L"Image/NPC_ClickNameSpace.png", L"Idle");

	animComp->SetCurrAnim(L"Idle");

	SetIsActive(false);

	GameObject::Init();
}

void NPCToolList::OnExecuteToIdle()
{
	SetIsActive(false);
}

void NPCToolList::OnEnable()
{
	SetPosition(Input::GetMousePosition());

	vector<GameObject*> childs = GetChilds();

	size_t count = GetChilds().size();

	const LONG& sizeX = 100;
	LONG sizeY = 21 * (LONG)count;

	GetComponent<RectColliderComponent>()->SetRectSize({ 0,0,sizeX,sizeY });

	for (size_t i = 0; i < count; ++i)
	{
		childs[i]->SetPosition({ GetX(),GetY() + 21 });
	}
}
