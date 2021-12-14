#include "stdafx.h"
#include "TextComponent.h"

TextComponent::TextComponent(const wchar_t* text, const wchar_t* font, float size, D2D1::ColorF color, GameObject* owner, INT32 order) noexcept
	:Component(owner, order)
{
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(mpDWriteFactory), reinterpret_cast<IUnknown**>(&mpDWriteFactory));
	mpDWriteFactory->CreateTextFormat(
		font,							// 폰트 패밀리 이름의 문자열
		NULL,							// 폰트 컬렉션 객체, NULL=시스템 폰트 컬렉션
		DWRITE_FONT_WEIGHT_THIN,		// 폰트 굵기. LIGHT, NORMAL, BOLD 등.
		DWRITE_FONT_STYLE_NORMAL,		// 폰트 스타일. NORMAL, OBLIQUE, ITALIC.
		DWRITE_FONT_STRETCH_NORMAL,		// 폰트 간격. CONDENSED, NORMAL, MEDIUM, EXTEXDED 등.
		size,							// 폰트 크기.
		L"ko",							// 로케일을 문자열로 명시.  영어-미국=L"en-us", 한국어-한국=L"ko-kr"
		&mpTextFormat
	);

	mpTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);            // 문단 센터 정렬
	mpTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);  // 문장 내의 수직 정렬
	gpRenderTarget->CreateSolidColorBrush(color, &mpBrush);
	mpText = text;
}

void TextComponent::Render()
{
	gpRenderTarget->DrawTextW(
		mpText,							// WCHAR* 문자열
		(UINT32)wcslen(mpText),			// 문자의 개수
		mpTextFormat,					// IDWriteTextFormat 텍스트 포맷 
		D2D1::RectF((FLOAT)mRect.left, (FLOAT)mRect.top, (FLOAT)mRect.right, (FLOAT)mRect.bottom),	// 그려질 영역의 크기와 위치.
		mpBrush							// 붓(brush)
	);
}

void TextComponent::SetRect(RECT rect) noexcept
{
	mRect = rect;
}
