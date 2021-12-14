#pragma once
#include "GameObject.h"

class Image;
class Sprite : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~Sprite() noexcept = default;

	virtual void Render() override;

	void SetImage(Image* img);
private:
	Image* mpImage = nullptr;
};
