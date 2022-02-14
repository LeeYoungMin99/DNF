#pragma once
#include "IBehaviour.h"

class GameObject;
class AnimatorComponent;
class Transition : public IBehaviour
{
private:
	using function = function<bool(const int&)>;
public:
	Transition(function func, const wstring& nextAnimTag, int transitionData, AnimatorComponent* animComp);
	virtual ~Transition() = default;

	virtual void Init() override {}
	virtual void Render() override {}
	virtual void Release() override {}

	virtual void Update() override;

	wstring				GetConnectAnimationTag() const { return _ConnectAnimationTag; }
private:
	AnimatorComponent*	_animComp = nullptr;
	int					_transitionData = 0;
	wstring				_ConnectAnimationTag = {};
	function			_callback = {};
};
