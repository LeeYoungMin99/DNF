#pragma once
#include "Config.h"

class BmpImage
{
public:
	enum ImageLoadType
	{
		Resource,		// 프로그램에 포함되는 데이터
		File,			// 실행 시간에 외부에서 로드하는 데이터
		Empty,			// 빈 비트맵 이미지 파일
		End
	};

	// class와 struct의 문법적인 차이
	// 접근지정자가 public이냐 private이냐
	typedef struct tagImageInfo
	{
		HDC hMemDc;		// 이미지 데이터를 관리하는 핸들(메모리 관리자)
		HBITMAP hBitmap;// 이미지 데이터
		HBITMAP hOldBit;// 기존 이미지 데이터
		int width;		// 가로 크기
		int height;		// 세로 크기
		BYTE loadType;	// 로드 타입

		// 애니메이션 용 데이터
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int currFrameX;
		int currFrameY;

		tagImageInfo()
		{
			hMemDc = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = ImageLoadType::Empty;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			currFrameX = 0;
			currFrameY = 0;
		};
	} IMAGE_INFO, *LPIMAGE_INFO;

	//struct testImageInfo : public tagImageInfo
	//{

	//};

	//tagImageInfo imageInfo;
	//IMAGE_INFO imageInfo2;

	//tagImageInfo* imageInfo;
	//LPIMAGE_INFO imageInfo3;

private:
	LPIMAGE_INFO imageInfo = nullptr;
	bool isTransparent = false;
	COLORREF transColor = {};

public:
	~BmpImage() = default;
	HRESULT Init(int width, int height);	// 빈 비트맵 이미지 생성(Empty)
	HRESULT Init(const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = NULL); // File 프레임이 없는 이미지
	HRESULT Init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = NULL); // File 프레임이 있는 이미지

	void Release();	// 메모리 해제

	void Render(HDC hdc);
	void Render(HDC hdc, int destX, int destY);	// 이미지 데이터를 화면에 복사
	void Render(HDC hdc, int destX, int destY, int frameX, int frameY, float scale = 1.0f);	// 이미지 데이터를 화면에 복사

	HDC GetMemDC() { if (imageInfo) return imageInfo->hMemDc; return NULL; }

	LPIMAGE_INFO GetImageInfo() { return imageInfo; }

	int GetCurrFrameX() { return imageInfo->currFrameX; }
	void SetCurrFrameX(int frame) { imageInfo->currFrameX = frame; }
	int GetCurrFrameY() { return imageInfo->currFrameY; }
	void SetCurrFrameY(int frame) { imageInfo->currFrameY = frame; }

	int GetMaxFrameX() { return imageInfo->maxFrameX; }
	int GetMaxFrameY() { return imageInfo->maxFrameY; }

	int GetFrameWidth() { return imageInfo->frameWidth; }
	int GetFrameHeight() { return imageInfo->frameHeight; }

	int GetWidth() { return imageInfo->width; }
	int GetHeight() { return imageInfo->height; }
};

