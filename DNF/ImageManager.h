#pragma once
#include "Singleton.h"

class Image;
class ImageManager : public Singleton<ImageManager>
{
public:
	ImageManager() = default;
	virtual ~ImageManager() noexcept;

	void Init();

	Image* AddImage(const wchar_t* path, int maxFrameX, int correctX = 0, int correctY = 0, float animationSpeed = 0.0f, bool loop = false);
	Image* FindImage(wstring path);
private:
	unordered_map<wstring, Image*> mpImages = {};
};

