#include "stdafx.h"
#include "MapCollider.h"

#include "PositionComponent.h"
#include "RectColliderComponent.h"
#include "BodyCollisionComponent.h"

MapCollider::MapCollider(const RECT& size, Scene* scene, const wstring& tag)
	:GameObject(scene, tag)
{
	PositionComponent* posComp = new PositionComponent(this);

	BodyCollisionComponent* ColliderComp = new BodyCollisionComponent(new RectColliderComponent(size, this),0,0, this);
}
