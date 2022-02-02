#include "stdafx.h"
#include "AnimatorComponent.h"

#include "Animation.h"
#include "Transition.h"

AnimatorComponent::~AnimatorComponent()
{
	for (auto& anim : _animations)
	{
		SAFE_RELEASE(anim.second);
	}

	for (auto& graph : _graph)
	{
		for (auto& transition : graph.second)
		{
			SAFE_RELEASE(transition);
		}
	}
}

void AnimatorComponent::Update()
{
	_curAnim->Update();

	for (auto& transition : _graph[_curAnim->GetAnimTag()])
	{
		transition->Update();
	}

	for (auto& transition : _graph[_curAnim->GetAnimTag()])
	{
		if (_boolParams[transition->GetNextAnimTag()])
		{
			_boolParams[transition->GetNextAnimTag()] = false;

			_curAnim = _animations[transition->GetNextAnimTag()];

			_curAnim->Init();
		}
	}
}

void AnimatorComponent::AddAnimation(const wstring& path, const wstring& animTag)
{
	_animations[animTag] = new Animation(path, animTag);
}

void AnimatorComponent::AddTransition(const wstring& start, const wstring& end, const int& transitionValue, function func)
{
	_graph[start].push_back(new Transition(func, end, transitionValue, this));
	_graph[end].push_back(new Transition(func, L"Idle", 1, this));
}

void AnimatorComponent::AddTransition(const wstring& start, const wstring& end, function func, const int& transitionValue)
{
	_graph[start].push_back(new Transition(func, end, transitionValue, this));
}

void AnimatorComponent::AddTransition(const wstring& end, function func, const int& transitionValue)
{
	for (auto transition : _graph)
	{
		_graph[transition.first].push_back(new Transition(func, end, transitionValue, this));
	}
}
