#pragma once

class Image
{
public:
	typedef struct tagImageInfo
	{
		// 애니메이션 용 데이터
		ID2D1Bitmap* pBitmap = nullptr;
		int maxFrameX = 0;
		int maxFrameY = 0;
		D2D1_SIZE_F imageFrameSize = {};
		float animationSpeed = 0.0f;
		bool bIsLoop = false;

	} IMAGE_INFO, * LPIMAGE_INFO;

public:
	HRESULT Init(LPCWCHAR path, int maxFrameX, int maxFrameY, float animationSpeed = 0.0f, bool loop = false);
	void Release();

	ID2D1Bitmap* GetBitmap() noexcept;
	int GetMaxFrameX() const noexcept;
	int GetMaxFrameY() const noexcept;
	D2D1_SIZE_F GetImageFrameSize() const noexcept;
	float GetAnimationSpeed() const noexcept;
	bool GetIsLoop() const noexcept;
private:
	LPIMAGE_INFO imageInfo = nullptr;
};
