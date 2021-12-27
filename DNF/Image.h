#pragma once

class Image
{
private:
	typedef struct tagImageInfo
	{
		// 애니메이션 용 데이터
		ID2D1Bitmap* pBitmap = nullptr;
		D2D1_SIZE_F	 imageFrameSize = {};
		float		 animationSpeed = 0.0f;
		int			 maxFrameX = 0;
		int			 canCancelFrame = 0;
		int			 correctX = 0;
		int			 correctY = 0;
		bool		 bIsLoop = false;

	} IMAGE_INFO, * LPIMAGE_INFO;

public:
	HRESULT Init(LPCWCHAR path, const int& maxFrameX, const int& canCancelFrame = 100, const int& correctX = 0, const int& correctY = 0, const float& animationSpeed = 0.0f, const bool& loop = false);
	void Release() { SAFE_DELETE(_imageInfo); }

	ID2D1Bitmap*	GetBitmap()			const { return _imageInfo->pBitmap; }
	D2D1_SIZE_F		GetImageFrameSize() const { return _imageInfo->imageFrameSize; }
	float			GetAnimationSpeed()	const { return _imageInfo->animationSpeed; }
	int				GetMaxFrameX()		const { return _imageInfo->maxFrameX; }
	int				GetCanCancelFrame()	const { return _imageInfo->canCancelFrame; }
	int				GetCorrectX()		const { return _imageInfo->correctX; }
	int				GetCorrectY()		const { return _imageInfo->correctY; }
	bool			GetIsLoop()			const { return _imageInfo->bIsLoop; }
private:
	LPIMAGE_INFO	_imageInfo = nullptr;
};
