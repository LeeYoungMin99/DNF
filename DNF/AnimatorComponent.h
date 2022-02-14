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
	void			AddTransition(const wstring& start, const wstring& end, const int& transitionData, function func);
	void			AddTransition(const wstring& start, const wstring& end, function func, const int& transitionData);
	void			AddTransition(const wstring& end, function func, const int& transitionData);

	void			SetCurAnimation(const wstring& animTag)			{ _curAnimation = _animations[animTag]; }
	void			SetBoolParams(const wstring& tag, bool b)		{ _boolParams[tag] = b; }

	Animation*		GetCurAnimation() const							{ return _curAnimation; }
private:
	unordered_map<wstring, vector<Transition*>>	_graph;
	unordered_map<wstring, Animation*>			_animations;
	unordered_map<wstring, bool>				_boolParams;
	Animation*									_curAnimation = nullptr;
};

