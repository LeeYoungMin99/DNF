#include "stdafx.h"
#include "newAnimatorComponent.h"

#include "Animation.h"

newAnimatorComponent::~newAnimatorComponent() noexcept
{
}

void newAnimatorComponent::Update()
{
	if (mpCurrAnim->GetIsEnd())
	{

		for (auto nextAnim : mpAnimationGraph[mpCurrAnim->GetAnimTag()])
		{
			if (nextAnim->CanChange())
			{
				mpCurrAnim = nextAnim;
			}
		}

	}
}

Animation* newAnimatorComponent::GetCurrAnim() noexcept
{
	return mpCurrAnim;
}
