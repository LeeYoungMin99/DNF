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

	for (auto& nextAnim : _graph[_curAnim->GetAnimTag()])
	{
		nextAnim->Update();
	}

	for (auto& nextAnim : _graph[_curAnim->GetAnimTag()])
	{
		if (_boolParams[nextAnim->GetNextAnimTag()])
		{
			_boolParams[nextAnim->GetNextAnimTag()] = false;

			_curAnim = _animations[nextAnim->GetNextAnimTag()];

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
	_graph[end].push_back(new Transition(func, L"Idle", 0, this));
}

void AnimatorComponent::AddTransition(const wstring& start, const wstring& end, function func, const int& transitionValue)
{
	_graph[start].push_back(new Transition(func, end, transitionValue, this));
}