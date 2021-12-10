#pragma once
#include "Component.h"

class RectComponent : public Component
{
public:
	using Component::Component;
	virtual ~RectComponent() noexcept = default;

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetRect(RECT rect) noexcept;
	RECT GetRect() const;
private:
	void TurnoffRender() noexcept;
	void TurnonRender() noexcept;
private:
	RECT mRect = {};
	bool mbIsRender = true;
};
