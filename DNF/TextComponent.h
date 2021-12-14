#pragma once
#pragma once
#include "Component.h"

class TextComponent : public Component
{
public:
	TextComponent(const wchar_t* text, const wchar_t* font, float size, D2D1::ColorF color,GameObject* owner, INT32 order = 100) noexcept;
	virtual ~TextComponent() noexcept = default;

	virtual void Render() override;
	void SetRect(RECT rect) noexcept;

private:
	IDWriteFactory* mpDWriteFactory = nullptr;
	IDWriteTextFormat* mpTextFormat = nullptr;
	ID2D1SolidColorBrush* mpBrush = nullptr;
	const wchar_t* mpText = nullptr;
	RECT mRect = {};
};
