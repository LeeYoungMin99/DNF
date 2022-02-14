#include "stdafx.h"
#include "Animation.h"

#include "Image.h"
#include "ImageManager.h"

Animation::Animation(const wstring& path, const wstring& animTag)
{
	_image = ImageManager::GetSingleton()->FindImage(path);
	_animationTag = animTag;

	_maxFrame		= _image->GetMaxFrameX();
	_canCancelFrame = _image->GetCanCancelFrame();
	_animationSpeed = _image->GetAnimationSpeed();
	_bIsLoop		= _image->GetIsLoop();
}

void Animation::Init()
{
	SetCurrFrame(0);
	SetIsEnd(false);
	SetCanCancel(false);
	_elapsedTime = 0.0f;
}

void Animation::Update()
{
	_elapsedTime += Timer::GetDeltaTime();

	if (_elapsedTime >= _animationSpeed)
	{
		_elapsedTime -= _animationSpeed;

		++_curFrame;

		if (_canCancelFrame == _curFrame)
		{
			_bCanCancel = true;
		}

		if (_maxFrame == _curFrame)
		{
			if (_bIsLoop)
			{
				_curFrame = 0;
			}
			else
			{
				_curFrame -= 1;
				_bIsEnd = true;
			}
		}
	}
}
