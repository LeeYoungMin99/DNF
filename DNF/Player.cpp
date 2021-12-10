#include "stdafx.h"
#include "Player.h"

#include "AnimatorComponent.h"
#include "SpriteComponent.h"

void Player::Init()
{
	AnimatorComponent* animatorComp = new AnimatorComponent(this);
}

void Player::Update()
{
}
