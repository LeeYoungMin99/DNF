#include "stdafx.h"
#include "newSpriteComponent.h"

#include "newAnimatorComponent.h"
#include "Animation.h"
#include "GameObject.h"
#include "Character.h"
#include "CameraManager.h"

newSpriteComponent::newSpriteComponent(newAnimatorComponent* animatorComp, GameObject* owner, INT32 order) noexcept
	:Component(owner, order)
{
	mpAnimatorComp = animatorComp;
}

void newSpriteComponent::Render()
{
	int test = 100;


	FLOAT imageFrameSizeX = mpAnimatorComp->GetCurrAnim()->GetImage()->GetImageFrameSize().width;
	FLOAT imageFrameSizeY = mpAnimatorComp->GetCurrAnim()->GetImage()->GetImageFrameSize().height;
	LONG renderPosX = mpOwner->GetX() + mpAnimatorComp->GetCurrAnim()->GetImage()->GetCorrectX() + CameraManager::GetSingleton()->GetX() + test;
	LONG renderPosY = mpOwner->GetY() + mpAnimatorComp->GetCurrAnim()->GetImage()->GetCorrectY() + CameraManager::GetSingleton()->GetY();
	LONG renderPosZ = 0;
	FLOAT renderSizeX = renderPosX + imageFrameSizeX;
	FLOAT renderSizeY = renderPosY + imageFrameSizeY;
	FLOAT currFrame = mpAnimatorComp->GetCurrAnim()->GetCurrFrame() * imageFrameSizeX;
	FLOAT nextFrame = currFrame + imageFrameSizeX;
	LONG flipCenterX = mpOwner->GetX() + CameraManager::GetSingleton()->GetX()+ test;
	LONG flipCenterY = mpOwner->GetY() + CameraManager::GetSingleton()->GetY();

	if (dynamic_cast<Character*>(mpOwner))
	{
		renderPosZ = ((Character*)mpOwner)->GetZ();

		gpRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(1.3f, 1.3f, D2D1_POINT_2F{ (float)flipCenterX,(float)flipCenterY }));

		if (((Character*)mpOwner)->GetDirX() == Character::eDirX::Left)
			gpRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(-1.3f, 1.3f, D2D1_POINT_2F{ (float)flipCenterX,(float)flipCenterY }));
	}

	gpRenderTarget->DrawBitmap(mpAnimatorComp->GetCurrAnim()->GetImage()->GetBitmap()
		, D2D1::RectF((FLOAT)renderPosX, (FLOAT)renderPosY - renderPosZ, renderSizeX, renderSizeY - renderPosZ)
		, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
		, D2D1::RectF(currFrame, 0, nextFrame, imageFrameSizeY));

	gpRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1_POINT_2F{ 0,0 }));
}
