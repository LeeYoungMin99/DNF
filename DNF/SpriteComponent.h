#pragma once
#include "Component.h"

class AnimatorComponent;
class PositionComponent;
class TransformComponent;
class SpriteComponent : public Component
{
public:
	using Component::Component;
	virtual ~SpriteComponent()  = default;

	virtual void Init() override;
	virtual void Render() override;

	void ImageRender(
		const FLOAT& renderPosX, 
		const FLOAT& renderPosY, 
		const FLOAT& renderSizeX, 
		const FLOAT& renderSizeY,
		const FLOAT& currFrameStart, 
		const FLOAT& currFrameEnd, 
		const FLOAT& imageFrameSizeY);
private:
	AnimatorComponent*		_animComp = nullptr;
	PositionComponent*		_posComp = nullptr;
	TransformComponent*		_transformComp = nullptr;
};

