#include "stdafx.h"
#include "Transition.h"

#include "AnimatorComponent.h"

Transition::Transition(function func, const wstring& nextAnimTag, int transitionValue, AnimatorComponent* animComp)
	:_callback{ func }, _nextAnimTag{ nextAnimTag }, _transitionValue{ transitionValue}, _animComp{ animComp } {}

void Transition::Update()
{
	if (_callback(_transitionValue))
	{
		_animComp->SetBoolParams(_nextAnimTag, true);
	}
}
