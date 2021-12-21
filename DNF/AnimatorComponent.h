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
	void Pause();
	void PlayIdle();

	SpriteComponent* FindSprite(wstring tag);

	void SetCurrFrame(int frame) noexcept;

	SpriteComponent* GetCurrSprite() noexcept;
	wstring GetCurrSpriteTag() noexcept;
	int GetCurrFrame() const noexcept;
	bool GetIsPause() const noexcept;
	bool mbIsPause = false;
private:
	// Ű������ ��������Ʈ�� ã�°� �ƴ϶�
	// ���͸� �̿��ؼ� �ε����������� �ٲ� ����� �����غ���.
	unordered_map<wstring, SpriteComponent*> mpSprites;
	SpriteComponent* mpCurrSprite = nullptr;

	wstring mCurrSpriteTag = {};
	float mElapsedTime = 0.0f;
	float mAnimationSpeed = 0.0f;
	int mMaxFrameX = 0;
	bool mbIsLoop = false;
};

