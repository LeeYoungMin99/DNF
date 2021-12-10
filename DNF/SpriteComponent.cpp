#include "stdafx.h"
#include "SpriteComponent.h"

#include "GameObject.h"
#include "ImageManager.h"
#include "Image.h"

SpriteComponent::SpriteComponent(wstring path, GameObject* owner, INT32 order)
	:Component(owner, order)
{
	mpSprite = ImageManager::GetSingleton()->FindImage(path);
}

Image* SpriteComponent::GetSprite() const
{
	return mpSprite;
}
