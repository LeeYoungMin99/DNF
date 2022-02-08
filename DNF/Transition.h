#pragma once
#include "IBehaviour.h"

class GameObject;
class AnimatorComponent;
class Transition : public IBehaviour
{
private:
	using function = function<bool(const int&)>;
public:
	Transition(function func, const wstring& nextAnimTag, int transitionValue, AnimatorComponent* animComp);
	virtual ~Transition() = default;

	virtual void Init() override {}
	virtual void Render() override {}
	virtual void Release() override {}

	virtual void Update() override;

	wstring				GetNextAnimTag() const { return _nextAnimTag; }
private:
	AnimatorComponent*	_animComp = nullptr;
	int					_transitionValue = 0;
	wstring				_nextAnimTag = {};
	function			_callback = {};
};
