#pragma once
#include "IBehaviour.h"

class Image;
class Animation : public IBehaviour
{
public:
	Animation(const wstring& path, const wstring& animTag);

	virtual ~Animation() = default;

	virtual void Render() override {}
	virtual void Release() override {}

	virtual void Init() override;
	virtual void Update() override;

	wstring		GetAnimTag()	const  { return _animTag; }
	Image*		GetImage()		const  { return _image; }
	int			GetCurFrame()	const  { return _curFrame; }
	bool		IsEnd()			const  { return _bIsEnd; }
	bool		CanCancel()		const  { return _bCanCancel; }

	void		SetCurrFrame(int frame)	{ _curFrame = frame; }
	void		SetIsEnd(bool b)		{ _bIsEnd = b; }
	void		SetCanCancel(bool b)	{ _bCanCancel = b; }
private:
	Image*		_image = nullptr;
	wstring		_animTag = {};
	int			_curFrame = 0;
	int			_maxFrame = 0;
	int			_canCancelFrame = 0;
	float		_elapsedTime = 0.0f;
	float		_animationSpeed = 0.0f;
	bool		_bIsLoop = false;
	bool		_bIsEnd = false;
	bool		_bCanCancel = false;
};

