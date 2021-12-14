#pragma once
#include "Component.h"

class SpriteComponent;
class AnimatorComponent : public Component
{
public:
	using Component::Component;
	~AnimatorComponent() = default;

	virtual void Init() override;
	virtual void Update() override;

	void AddSprite(SpriteComponent* spriteComp, wstring tag);
	void Play(wstring tag);
	void PlayIdle();

	SpriteComponent* FindSprite(wstring tag);

	void SetCurrFrame(int frame) noexcept;

	SpriteComponent* GetCurrSprite() noexcept;
	wstring GetCurrSpriteTag() noexcept;
public:
	int mCurrFrame = 0;
private:
	unordered_map<wstring, SpriteComponent*> mpSprites;
	SpriteComponent* mpCurrSprite = nullptr;

	wstring mCurrSpriteTag = {};
	float mElapsedTime = 0.0f;
	float mAnimationSpeed = 0.0f;
	int mMaxFrameX = 0;
	bool mbIsLoop = 0;
};

