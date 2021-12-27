#pragma once
#pragma once
#include "Component.h"

class TextComponent : public Component
{
public:
	TextComponent(const wchar_t* text, const wchar_t* font, float size, D2D1::ColorF color,GameObject* owner, INT32 order = 100);
	virtual ~TextComponent() = default;

	virtual void Render() override;
	void SetRect(const RECT& rect) { _rect = rect; }
private:
	IDWriteFactory*			_dWriteFactory = nullptr;
	IDWriteTextFormat*		_textFormat = nullptr;
	ID2D1SolidColorBrush*	_brush = nullptr;
	const wchar_t*			_text = nullptr;
	RECT					_rect = {};
};
