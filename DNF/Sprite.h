#pragma once
#include "GameObject.h"

class Image;
class Sprite : public GameObject
{
public:
	Sprite(const wstring& path, Scene* scene, const std::wstring& tag, int order = 0);
	virtual ~Sprite() = default;

	virtual void Render() override;

	void		SetImage(Image* img);
private:
	Image*		_image = nullptr;
	int			_order = 0;
};
