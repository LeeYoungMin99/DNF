#pragma once

class Image
{
private:
	typedef struct tagImageInfo
	{
		// 애니메이션 용 데이터
		ID2D1Bitmap* _bitmap = nullptr;
		D2D1_SIZE_F	 _imageFrameSize = {};
		float		 _animationSpeed = 0.0f;
		int			 _maxFrameX = 0;
		int			 _canCancelFrame = 0;
		int			 _correctX = 0;
		int			 _correctY = 0;
		bool		 _bIsLoop = false;

	} IMAGE_INFO, * LPIMAGE_INFO;

public:
	HRESULT Init(LPCWCHAR path, 
		const int& maxFrameX, 
		const int& canCancelFrame = 100, 
		const int& correctX = 0, 
		const int& correctY = 0, 
		const float& animationSpeed = 0.0f, 
		const bool& loop = false);
	void Release() { SAFE_DELETE(_imageInfo); }

	ID2D1Bitmap*	GetBitmap()			const { return _imageInfo->_bitmap; }
	D2D1_SIZE_F		GetImageFrameSize() const { return _imageInfo->_imageFrameSize; }
	float			GetAnimationSpeed()	const { return _imageInfo->_animationSpeed; }
	int				GetMaxFrameX()		const { return _imageInfo->_maxFrameX; }
	int				GetCanCancelFrame()	const { return _imageInfo->_canCancelFrame; }
	int				GetCorrectX()		const { return _imageInfo->_correctX; }
	int				GetCorrectY()		const { return _imageInfo->_correctY; }
	bool			GetIsLoop()			const { return _imageInfo->_bIsLoop; }
private:
	LPIMAGE_INFO	_imageInfo = nullptr;
};
