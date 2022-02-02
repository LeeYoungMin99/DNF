#pragma once
#include "Component.h"

class Animation;
class Transition;
class AnimatorComponent : public Component
{
private:
	using function = function<bool(const int&)>;
public:
	using Component::Component;
	virtual ~AnimatorComponent();

	virtual void Update() override;

	void			AddAnimation(const wstring& path, const wstring& animTag);
	void			AddTransition(const wstring& start, const wstring& end, const int& transitionValue, function func);
	void			AddTransition(const wstring& start, const wstring& end, function func, const int& transitionValue);
	void			AddTransition(const wstring& end, function func, const int& transitionValue);

	void			SetCurrAnim(const wstring& animTag)			{ _curAnim = _animations[animTag]; }
	void			SetBoolParams(const wstring& tag, bool b)	{ _boolParams[tag] = b; }

	Animation*		GetCurAnim() const							{ return _curAnim; }
private:
	unordered_map<wstring, vector<Transition*>>	_graph;
	unordered_map<wstring, Animation*>			_animations;
	unordered_map<wstring, bool>				_boolParams;
	Animation*									_curAnim = nullptr;
};

