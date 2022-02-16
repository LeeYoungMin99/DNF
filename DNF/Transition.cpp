#include "stdafx.h"
#include "Transition.h"

#include "AnimatorComponent.h"

Transition::Transition(function func, const wstring& nextAnimTag, int transitionData, AnimatorComponent* animComp)
	:_callback{ func }, _ConnectAnimationTag{ nextAnimTag }, _transitionData{ transitionData}, _animComp{ animComp } {}

void Transition::Update()
{
	if (true == _callback(_transitionData))
	{
		_animComp->SetBoolParams(_ConnectAnimationTag, true);
	}
}
