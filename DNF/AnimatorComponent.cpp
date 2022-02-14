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
	_curAnimation->Update();

	for (auto& transition : _graph[_curAnimation->GetAnimationTag()])
	{
		transition->Update();

		if (true == _boolParams[transition->GetConnectAnimationTag()])
		{
			_boolParams[transition->GetConnectAnimationTag()] = false;

			_curAnimation = _animations[transition->GetConnectAnimationTag()];

			_curAnimation->Init();
		}
	}
}

void AnimatorComponent::AddAnimation(const wstring& path, const wstring& animTag)
{
	_animations[animTag] = new Animation(path, animTag);
}

void AnimatorComponent::AddTransition(const wstring& start, const wstring& end, const int& transitionData, function func)
{
	_graph[start].push_back(new Transition(func, end, transitionData, this));
	_graph[end].push_back(new Transition(func, L"Idle", 1, this));
}

void AnimatorComponent::AddTransition(const wstring& start, const wstring& end, function func, const int& transitionData)
{
	_graph[start].push_back(new Transition(func, end, transitionData, this));
}

void AnimatorComponent::AddTransition(const wstring& end, function func, const int& transitionData)
{
	for (auto transition : _graph)
	{
		_graph[transition.first].push_back(new Transition(func, end, transitionData, this));
	}
}
