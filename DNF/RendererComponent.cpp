#include "stdafx.h"
#include "RendererComponent.h"

#include "SpriteComponent.h"
#include "AnimatorComponent.h"
#include "Image.h"
#include "GameObject.h"
#include "Character.h"

RendererComponent::RendererComponent(AnimatorComponent* animatorComp, GameObject* owner, INT32 order) noexcept
	:Component(owner, order)
{
	mpAnimatorComp = animatorComp;
}

void RendererComponent::Render()
{
	FLOAT imageFrameSizeX = mpAnimatorComp->GetCurrSprite()->GetSprite()->GetImageFrameSize().width;
	FLOAT imageFrameSizeY = mpAnimatorComp->GetCurrSprite()->GetSprite()->GetImageFrameSize().height;
	LONG renderPosX = mpOwner->GetX() + mpAnimatorComp->GetCurrSprite()->GetSprite()->GetCorrectX();
	LONG renderPosY = mpOwner->GetY() + mpAnimatorComp->GetCurrSprite()->GetSprite()->GetCorrectY();
	LONG renderPosZ = 0;
	FLOAT renderSizeX = renderPosX + imageFrameSizeX;
	FLOAT renderSizeY = renderPosY + imageFrameSizeY;
	FLOAT mCurrFrame = mpAnimatorComp->GetCurrSprite()->mCurrFrame * imageFrameSizeX;
	FLOAT nextFrame = mCurrFrame + imageFrameSizeX;

	if (dynamic_cast<Character*>(mpOwner))
	{
		renderPosZ = ((Character*)mpOwner)->GetZ();
	}

	gpRenderTarget->DrawBitmap(mpAnimatorComp->GetCurrSprite()->GetSprite()->GetBitmap()
		, D2D1::RectF((FLOAT)renderPosX, (FLOAT)renderPosY - renderPosZ, renderSizeX, renderSizeY - renderPosZ)
		, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
		, D2D1::RectF(mCurrFrame, 0, nextFrame, imageFrameSizeY));
}
