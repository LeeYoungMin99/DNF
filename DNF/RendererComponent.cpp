#include "stdafx.h"
#include "RendererComponent.h"

#include "SpriteComponent.h"
#include "AnimatorComponent.h"
#include "Image.h"
#include "GameObject.h"
#include "Character.h"

#include "CameraManager.h"

RendererComponent::RendererComponent(AnimatorComponent* animatorComp, GameObject* owner, INT32 order) noexcept
	:Component(owner, order)
{
	mpAnimatorComp = animatorComp;
}

void RendererComponent::Render()
{
	FLOAT imageFrameSizeX = mpAnimatorComp->GetCurrSprite()->GetSprite()->GetImageFrameSize().width;
	FLOAT imageFrameSizeY = mpAnimatorComp->GetCurrSprite()->GetSprite()->GetImageFrameSize().height;
	LONG renderPosX = mpOwner->GetX() + mpAnimatorComp->GetCurrSprite()->GetSprite()->GetCorrectX() + CameraManager::GetSingleton()->GetX();
	LONG renderPosY = mpOwner->GetY() + mpAnimatorComp->GetCurrSprite()->GetSprite()->GetCorrectY() + CameraManager::GetSingleton()->GetY();
	LONG renderPosZ = 0;
	FLOAT renderSizeX = renderPosX + imageFrameSizeX;
	FLOAT renderSizeY = renderPosY + imageFrameSizeY;
	FLOAT currFrame = mpAnimatorComp->GetCurrSprite()->GetCurrFrame() * imageFrameSizeX;
	FLOAT nextFrame = currFrame + imageFrameSizeX;
	LONG flipCenterX = mpOwner->GetX() + CameraManager::GetSingleton()->GetX();
	LONG flipCenterY = mpOwner->GetY() + CameraManager::GetSingleton()->GetY();

	if (dynamic_cast<Character*>(mpOwner))
	{
		renderPosZ = ((Character*)mpOwner)->GetZ();

		gpRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(1.3f, 1.3f, D2D1_POINT_2F{ (float)flipCenterX,(float)flipCenterY }));

		if (((Character*)mpOwner)->GetDirX() == Character::eDirX::Left)
			gpRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(-1.3f, 1.3f, D2D1_POINT_2F{ (float)flipCenterX,(float)flipCenterY }));
	}

	gpRenderTarget->DrawBitmap(mpAnimatorComp->GetCurrSprite()->GetSprite()->GetBitmap()
		, D2D1::RectF((FLOAT)renderPosX, (FLOAT)renderPosY - renderPosZ, renderSizeX, renderSizeY - renderPosZ)
		, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
		, D2D1::RectF(currFrame, 0, nextFrame, imageFrameSizeY));

	gpRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1_POINT_2F{ 0,0 }));
}
