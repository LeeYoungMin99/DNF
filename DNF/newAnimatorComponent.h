#pragma once
#include "Component.h"
#include "Transition.h"

class Animation;
class newAnimatorComponent : public Component
{
private:
	using callback_t = bool(*)();
public:
	using Component::Component;
	virtual ~newAnimatorComponent() noexcept;

	virtual void Update() override;

	void AddAnimation(const wstring& path, const wstring& animTag);
	void AddTransition(const wstring& start, const wstring& end, callback_t func);

	void SetCurrAnim(const wstring& animTag);

	Animation* GetCurrAnim() noexcept;
private:
	unordered_map<wstring, vector<Transition<callback_t>>> mGraph;
	unordered_map<wstring, Animation*> mpAnimations;

	Animation* mpCurrAnim = nullptr;
};

