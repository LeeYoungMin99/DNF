#include "stdafx.h"
#include "RectColliderComponent.h"

#include "PositionComponent.h"
#include "TransformComponent.h"

#include "GameObject.h"

RectColliderComponent::RectColliderComponent(const RECT& rectSize, GameObject* owner, INT32 order)
	:Component(owner, order), _rectSize{ rectSize } {}

void RectColliderComponent::Init()
{
	_posComp = GetOwner()->GetComponent<PositionComponent>();
	_transformComp = GetOwner()->GetComponent<TransformComponent>();
}

void RectColliderComponent::Update()
{
	LONG ownerX, ownerY;

	if (_posComp != nullptr)
	{
		ownerX = (LONG)(_posComp->GetX());
		ownerY = (LONG)(_posComp->GetY());
	}
	else
	{
		ownerX = GetOwner()->GetX();
		ownerY = GetOwner()->GetY();
	}

	if (_transformComp != nullptr)
	{
		_rect.left = ownerX + _rectSize.left * (int)_transformComp->GetDirX();
		_rect.right = ownerX + _rectSize.right * (int)_transformComp->GetDirX();
		_rect.top = ownerY + _rectSize.top;
		_rect.bottom = ownerY + _rectSize.bottom;
	}
	else
	{
		_rect.left = ownerX + _rectSize.left;
		_rect.right = ownerX + _rectSize.right;
		_rect.top = ownerY + _rectSize.top;
		_rect.bottom = ownerY + _rectSize.bottom;
	}

	if (_rect.left > _rect.right)
	{
		std::swap(_rect.left, _rect.right);
	}

	if (Input::GetButtonDown('1'))
	{
		ChangeIsRender();
	}
}

void RectColliderComponent::Render()
{
	if (_bIsRender)
	{
		ID2D1SolidColorBrush* _brush = nullptr;

		gpRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1, 1), &_brush);
		gpRenderTarget->DrawRectangle(D2D1::RectF((FLOAT)(_rect.left), (FLOAT)(_rect.top - _posComp->GetZ()), (FLOAT)(_rect.right), (FLOAT)(_rect.bottom - _posComp->GetZ())), _brush, 1);
	}
}
