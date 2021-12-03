#pragma once
#include "Singleton.h"

class BmpImage;
class BmpImageManager : public Singleton<BmpImageManager>
{
public:
	virtual ~BmpImageManager() = default;

	void Init();
	void Release();

	BmpImage* AddImage(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = NULL);
	BmpImage* AddImage(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = NULL);
	BmpImage* FindImage(const char* fileName);
private:
	unordered_map<string, BmpImage*> images = {};
};

