#pragma once
#include "Component.h"

class Image;
class SpriteComponent : public Component
{
public:
	SpriteComponent(wstring path, GameObject* owner, INT32 order = 100) noexcept;
	virtual ~SpriteComponent() noexcept = default;

	Image* GetSprite() const noexcept;
public:
	int mCurrFrame = 0;
private:
	Image* mpSprite = nullptr;
};

