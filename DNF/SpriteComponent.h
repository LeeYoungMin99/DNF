#pragma once
#include "Component.h"

class Image;
class SpriteComponent : public Component
{
public:
	SpriteComponent(wstring path, GameObject* owner, INT32 order = 100);
	virtual ~SpriteComponent() noexcept = default;

	Image* GetSprite() const;
public:
	int currFrameX = 0;
	int currFrameY = 0;
private:
	Image* mpSprite = nullptr;
};

