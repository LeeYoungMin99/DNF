#pragma once
#include "Component.h"

class Image;
class SpriteComponent : public Component
{
public:
	SpriteComponent(wstring path, GameObject* owner, INT32 order = 100) noexcept;
	virtual ~SpriteComponent() noexcept = default;

	Image* GetSprite() const noexcept;
	int GetCurrFrame() const noexcept;

	void SetNextFrame() noexcept;
	void SetCurrFrame(int frame) noexcept;
private:
	int mCurrFrame = 0;
	Image* mpSprite = nullptr;
};

