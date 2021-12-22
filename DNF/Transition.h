#pragma once
#include "GameEntity.h"

class newAnimatorComponent;
class Animation;
template<typename T>
class Transition : public GameEntity
{
public:
	Transition(const T& func, const wstring& nextAnimTag, newAnimatorComponent* animComp)
	{
		mpCallback = func;
		mNextAnimTag = nextAnimTag;
		mpAnimComp = animComp;
	}

	virtual void Init() override {}
	virtual void Update() override {}
	virtual void Render() override {}
	virtual void Release() override {}

	bool CanChange()
	{
		return mpCallback();
	}

	wstring GetNextAnimTag() const noexcept
	{
		return mNextAnimTag;
	}

private:
	newAnimatorComponent* mpAnimComp = nullptr;

	wstring mNextAnimTag = {};

	T mpCallback = {};
};
