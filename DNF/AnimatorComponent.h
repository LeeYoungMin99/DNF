#pragma once
#include "Component.h"

class SpriteComponent;
class AnimatorComponent : public Component
{
public:
	using Component::Component;
	~AnimatorComponent() = default;

	virtual void Update() override;

	void AddSprite(SpriteComponent* spriteComp, wstring tag);
	void Play(wstring tag);
	void Stop(wstring tag);

	SpriteComponent* FindSprite(wstring tag);

	SpriteComponent* GetCurrSprite();
private:
	unordered_map<wstring, SpriteComponent*> mSprites;
	SpriteComponent* currSprite = nullptr;

	float mElapsedTime = 0.0f;
	float mAnimationSpeed = 0.0f;
	int mMaxFrameX = 0;
	int mMaxFrameY = 0;
	bool mbIsLoop = 0;
};

