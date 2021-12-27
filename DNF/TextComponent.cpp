#include "stdafx.h"
#include "TextComponent.h"

TextComponent::TextComponent(const wchar_t* text, const wchar_t* font, float size, D2D1::ColorF color, GameObject* owner, INT32 order) 
	:Component(owner, order)
{
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(_dWriteFactory), reinterpret_cast<IUnknown**>(&_dWriteFactory));
	_dWriteFactory->CreateTextFormat(
		font,							// 폰트 패밀리 이름의 문자열
		NULL,							// 폰트 컬렉션 객체, NULL=시스템 폰트 컬렉션
		DWRITE_FONT_WEIGHT_THIN,		// 폰트 굵기. LIGHT, NORMAL, BOLD 등.
		DWRITE_FONT_STYLE_NORMAL,		// 폰트 스타일. NORMAL, OBLIQUE, ITALIC.
		DWRITE_FONT_STRETCH_NORMAL,		// 폰트 간격. CONDENSED, NORMAL, MEDIUM, EXTEXDED 등.
		size,							// 폰트 크기.
		L"ko",							// 로케일을 문자열로 명시.  영어-미국=L"en-us", 한국어-한국=L"ko-kr"
		&_textFormat
	);

	_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);            // 문단 센터 정렬
	_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);  // 문장 내의 수직 정렬
	gpRenderTarget->CreateSolidColorBrush(color, &_brush);
	_text = text;
}

void TextComponent::Render()
{
	gpRenderTarget->DrawTextW(
		_text,							// WCHAR* 문자열
		(UINT32)wcslen(_text),			// 문자의 개수
		_textFormat,					// IDWriteTextFormat 텍스트 포맷 
		D2D1::RectF((FLOAT)_rect.left, (FLOAT)_rect.top, (FLOAT)_rect.right, (FLOAT)_rect.bottom),	// 그려질 영역의 크기와 위치.
		_brush							// 붓(brush)
	);
}