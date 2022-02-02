#pragma once
#include "Component.h"

class TransformComponent;
class PositionComponent;
class RectColliderComponent : public Component
{
public:
	RectColliderComponent(const RECT& rectSize, GameObject* owner, INT32 order = 100);
	virtual ~RectColliderComponent() = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void				SetRect(const RECT& rect) { _rect = rect; }
	void				SetRectSize(const RECT& rect) { _rectSize = rect; }

	const RECT			GetRect() const { return _rect; }
	const RECT			GetRectSize() const { return _rectSize; }
private:
	void				ChangeIsRender() { _bIsRender = !_bIsRender; }
private:
	RECT				_rect = {};
	RECT				_rectSize = {};
	bool				_bIsRender = false;
	PositionComponent*	_posComp = nullptr;
	TransformComponent* _transformComp = nullptr;
};
