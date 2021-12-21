#pragma once
#include "Component.h"

class RectComponent : public Component
{
public:
	using Component::Component;
	virtual ~RectComponent() noexcept = default;

	virtual void Update() override;
	virtual void Render() override;

	void SetRect(RECT rect) noexcept;
	void SetRectSize(RECT rect) noexcept;

	const RECT* GetRectAddress() const noexcept;
	const RECT GetRect() const noexcept;
private:
	void ChangeIsRender() noexcept;
private:
	RECT mRect = {};
	RECT mRectSize = {};
	bool mbIsRender = false;
};
