#pragma once
#include "Singleton.h"
#include "GameEntity.h"

class Image;
class ImageManager : public Singleton<ImageManager>, public IBehaviour
{
public:
	ImageManager() = default;
	virtual ~ImageManager();

	virtual void Init() override;
	virtual void Update() override {}
	virtual void Render() override {}
	virtual void Release() override {}

	Image*							AddImage(const wchar_t* path, 
											const int& maxFrameX, 
											const int& canCancelFrame = 100, 
											const int& correctX = 0, 
											const int& correctY = 0, 
											const float& animationSpeed = 0.0f, 
											const bool& loop = false);
	Image*							FindImage(const wstring& path);
private:
	unordered_map<wstring, Image*>	_images = {};
};

