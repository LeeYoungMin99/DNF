#include "stdafx.h"
#include "newAnimatorComponent.h"

#include "Animation.h"

newAnimatorComponent::~newAnimatorComponent() noexcept
{
	for (auto& anim : mpAnimations)
	{
		SAFE_RELEASE(anim.second);
	}
}

void newAnimatorComponent::Update()
{
	mpCurrAnim->Update();
	//for (auto& transition : mGraph[mpCurrAnim->GetAnimTag()])
	//{
	//	
	//}

	if (mpCurrAnim->IsEnd())
	{

		for (auto nextAnim : mGraph[mpCurrAnim->GetAnimTag()])
		{
			if (nextAnim.CanChange())
			{
				mpCurrAnim = mpAnimations[nextAnim.GetNextAnimTag()];
				mpCurrAnim->SetCurrFrame(0);

				if (mpCurrAnim->GetIsLoop() == false)
					mpCurrAnim->SetIsEnd(false);
			}
		}

	}
}

void newAnimatorComponent::AddAnimation(const wstring& path, const wstring& animTag)
{
	mpAnimations[animTag] = new Animation(path, animTag);
}

void newAnimatorComponent::AddTransition(const wstring& start, const wstring& end, callback_t func)
{
	mGraph[start].push_back(Transition<callback_t>(func, end, this));
}

Animation* newAnimatorComponent::GetCurrAnim() noexcept
{
	return mpCurrAnim;
}

void newAnimatorComponent::SetCurrAnim(const wstring& animTag)
{
	mpCurrAnim = mpAnimations[animTag];
}
