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
	const RECT* GetRectAddress() const;
private:
	void TurnoffRender() noexcept;
	void TurnonRender() noexcept;
private:
	RECT mRect = {};
	bool mbIsRender = true;
};
