#pragma once
#include "GameObject.h"

class MapCollider : public GameObject
{
public:
	MapCollider(const RECT& size, Scene* scene, const wstring& tag);
	virtual ~MapCollider() = default;
};

