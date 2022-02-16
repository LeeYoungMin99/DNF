#include "stdafx.h"
#include "SpriteComponent.h"

#include "Animation.h"
#include "GameObject.h"

#include "Image.h"
#include "PositionComponent.h"
#include "TransformComponent.h"
#include "AnimatorComponent.h"

void SpriteComponent::Init()
{
	_animComp = GetOwner()->GetComponent<AnimatorComponent>();

	_posComp = GetOwner()->GetComponent<PositionComponent>();
	_transformComp = GetOwner()->GetComponent<TransformComponent>();
}

void SpriteComponent::Render()
{
	FLOAT renderPosX, renderPosY;

	if (_posComp != nullptr)
	{
		renderPosX = (FLOAT)(_posComp->GetX() + _animComp->GetCurAnimation()->GetImage()->GetCorrectX());
		renderPosY = (FLOAT)(_posComp->GetY() + _animComp->GetCurAnimation()->GetImage()->GetCorrectY() - _posComp->GetZ());
	}
	else
	{
		renderPosX = (FLOAT)(GetOwner()->GetX() + _animComp->GetCurAnimation()->GetImage()->GetCorrectX());
		renderPosY = (FLOAT)(GetOwner()->GetY() + _animComp->GetCurAnimation()->GetImage()->GetCorrectY());
	}

	FLOAT imageFrameSizeY = _animComp->GetCurAnimation()->GetImage()->GetImageFrameSize().height;
	FLOAT imageFrameSizeX = _animComp->GetCurAnimation()->GetImage()->GetImageFrameSize().width;
	FLOAT renderSizeX = renderPosX + imageFrameSizeX;
	FLOAT renderSizeY = renderPosY + imageFrameSizeY;
	FLOAT currFrameStart = _animComp->GetCurAnimation()->GetCurFrame() * imageFrameSizeX;
	FLOAT currFrameEnd = currFrameStart + imageFrameSizeX;

	if (_transformComp != nullptr)
	{
		if (eDirX::Left == _transformComp->GetDirX())
		{
			FLOAT flipCenterX = (FLOAT)_posComp->GetX();
			FLOAT flipCenterY = (FLOAT)_posComp->GetY();

			_gRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1_POINT_2F{ flipCenterX,flipCenterY }));

			ImageRender(renderPosX, renderPosY, renderSizeX, renderSizeY, currFrameStart, currFrameEnd, imageFrameSizeY);

			_gRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1_POINT_2F{ 0,0 }));
		}
		else
		{
			ImageRender(renderPosX, renderPosY, renderSizeX, renderSizeY, currFrameStart, currFrameEnd, imageFrameSizeY);
		}
	}
	else
	{
		ImageRender(renderPosX, renderPosY, renderSizeX, renderSizeY, currFrameStart, currFrameEnd, imageFrameSizeY);
	}
}

void SpriteComponent::ImageRender(const FLOAT renderPosX, 
								  const FLOAT renderPosY, 
								  const FLOAT renderSizeX, 
								  const FLOAT renderSizeY, 
								  const FLOAT currFrameStart, 
								  const FLOAT currFrameEnd, 
								  const FLOAT imageFrameSizeY)
{
	_gRenderTarget->DrawBitmap(_animComp->GetCurAnimation()->GetImage()->GetBitmap()
		, D2D1::RectF(renderPosX, renderPosY, renderSizeX, renderSizeY)
		, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
		, D2D1::RectF(currFrameStart, 0, currFrameEnd, imageFrameSizeY));
}