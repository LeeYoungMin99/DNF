#include "stdafx.h"
#include "RendererComponent.h"

#include "SpriteComponent.h"
#include "AnimatorComponent.h"
#include "Image.h"
#include "GameObject.h"

RendererComponent::RendererComponent(AnimatorComponent* animatorComp, GameObject* owner, INT32 order)
	:Component(owner, order)
{
	mpAnimatorComp = animatorComp;
}

void RendererComponent::Render()
{
	LONG posX = mpOwner->GetX();
	LONG posY = mpOwner->GetY();
	FLOAT imageFrameSizeX = mpAnimatorComp->GetCurrSprite()->GetSprite()->GetImageFrameSize().width;
	FLOAT imageFrameSizeY = mpAnimatorComp->GetCurrSprite()->GetSprite()->GetImageFrameSize().height;
	FLOAT renderSizeX = posX + imageFrameSizeX;
	FLOAT renderSizeY = posY + imageFrameSizeY;
	FLOAT currFrameX = mpAnimatorComp->GetCurrSprite()->currFrameX * imageFrameSizeX;
	FLOAT currFrameY = mpAnimatorComp->GetCurrSprite()->currFrameY * imageFrameSizeY;
	FLOAT nextFrameX = currFrameX + imageFrameSizeX;
	FLOAT nextFrameY = currFrameY + imageFrameSizeY;

	gpRenderTarget->DrawBitmap(mpAnimatorComp->GetCurrSprite()->GetSprite()->GetBitmap()
		, D2D1::RectF((FLOAT)posX, (FLOAT)posY, renderSizeX, renderSizeY)
		, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
		, D2D1::RectF(currFrameX, currFrameY, nextFrameX, nextFrameY));
}
