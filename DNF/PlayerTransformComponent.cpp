#include "stdafx.h"
#include "PlayerTransformComponent.h"

#include "GameObject.h"

#include "StateMachineComponent.h"

void PlayerTransformComponent::Init()
{
	_stateMachineComp = GetOwner()->GetComponent<StateMachineComponent>();
}

void PlayerTransformComponent::Update()
{
	eState state = (eState)_stateMachineComp->GetCurStateTag();

	switch (state)
	{
	case eState::Idle:
	case eState::Walk:
	case eState::Run:
		if		(Input::GetButtonDown(VK_LEFT))		{ SetDirX(eDirX::Left); }		
		else if (Input::GetButtonDown(VK_RIGHT)) 	{ SetDirX(eDirX::Right); }

		if		(Input::GetButtonDown(VK_UP))	{ SetDirY(eDirY::Up); }
		else if (Input::GetButtonDown(VK_DOWN))	{ SetDirY(eDirY::Down); }

		if		(Input::GetButtonUp(VK_RIGHT) && Input::GetButton(VK_LEFT)) { SetDirX(eDirX::Left); }
		else if (Input::GetButtonUp(VK_LEFT) && Input::GetButton(VK_RIGHT)) { SetDirX(eDirX::Right); }

		if		(Input::GetButtonUp(VK_DOWN) && Input::GetButton(VK_UP)) { SetDirY(eDirY::Up); }
		else if (Input::GetButtonUp(VK_UP) && Input::GetButton(VK_DOWN)) { SetDirY(eDirY::Down); }

		if		(eDirX::Right == _dirX)	{ if (Input::GetButton(VK_LEFT) && false == (Input::GetButton(VK_RIGHT) || Input::GetButtonDown(VK_RIGHT))) { SetDirX(eDirX::Left); } }
		else if (eDirX::Left == _dirX) { if (Input::GetButton(VK_RIGHT) && false == (Input::GetButton(VK_LEFT) || Input::GetButtonDown(VK_LEFT))) { SetDirX(eDirX::Right); } }

		if		(eDirY::Down == _dirY)	{ if (Input::GetButton(VK_UP) && false == (Input::GetButton(VK_DOWN) || Input::GetButtonDown(VK_DOWN))) { SetDirY(eDirY::Up); } }
		else if (eDirY::Up == _dirY)	{ if (Input::GetButton(VK_DOWN) && false == (Input::GetButton(VK_UP) || Input::GetButtonDown(VK_UP))) { SetDirY(eDirY::Down); } }
		break;

	case eState::Jump:
	case eState::JumpAttack:
		if (Input::GetButtonDown(VK_LEFT)) { SetDirX(eDirX::Left); }
		else if (Input::GetButtonDown(VK_RIGHT)) { SetDirX(eDirX::Right); }

		if (Input::GetButtonDown(VK_UP)) { SetDirY(eDirY::Up); }
		else if (Input::GetButtonDown(VK_DOWN)) { SetDirY(eDirY::Down); }
		break;
	}
}
