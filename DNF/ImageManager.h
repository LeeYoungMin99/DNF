#pragma once
#include "Singleton.h"
#include "GameEntity.h"

class Image;
class ImageManager : public Singleton<ImageManager>, public GameEntity
{
public:
	ImageManager() = default;
	virtual ~ImageManager() noexcept;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	Image* AddImage(const wchar_t* path, int maxFrameX, int correctX = 0, int correctY = 0, float animationSpeed = 0.0f, bool loop = false);
	Image* FindImage(wstring path);
private:
	unordered_map<wstring, Image*> mpImages = {};

};

