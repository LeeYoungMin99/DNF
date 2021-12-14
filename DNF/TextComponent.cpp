#include "stdafx.h"
#include "TextComponent.h"

TextComponent::TextComponent(const wchar_t* text, const wchar_t* font, float size, D2D1::ColorF color, GameObject* owner, INT32 order) noexcept
	:Component(owner, order)
{
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(mpDWriteFactory), reinterpret_cast<IUnknown**>(&mpDWriteFactory));
	mpDWriteFactory->CreateTextFormat(
		font,							// ��Ʈ �йи� �̸��� ���ڿ�
		NULL,							// ��Ʈ �÷��� ��ü, NULL=�ý��� ��Ʈ �÷���
		DWRITE_FONT_WEIGHT_THIN,		// ��Ʈ ����. LIGHT, NORMAL, BOLD ��.
		DWRITE_FONT_STYLE_NORMAL,		// ��Ʈ ��Ÿ��. NORMAL, OBLIQUE, ITALIC.
		DWRITE_FONT_STRETCH_NORMAL,		// ��Ʈ ����. CONDENSED, NORMAL, MEDIUM, EXTEXDED ��.
		size,							// ��Ʈ ũ��.
		L"ko",							// �������� ���ڿ��� ���.  ����-�̱�=L"en-us", �ѱ���-�ѱ�=L"ko-kr"
		&mpTextFormat
	);

	mpTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);            // ���� ���� ����
	mpTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);  // ���� ���� ���� ����
	gpRenderTarget->CreateSolidColorBrush(color, &mpBrush);
	mpText = text;
}

void TextComponent::Render()
{
	gpRenderTarget->DrawTextW(
		mpText,							// WCHAR* ���ڿ�
		(UINT32)wcslen(mpText),			// ������ ����
		mpTextFormat,					// IDWriteTextFormat �ؽ�Ʈ ���� 
		D2D1::RectF((FLOAT)mRect.left, (FLOAT)mRect.top, (FLOAT)mRect.right, (FLOAT)mRect.bottom),	// �׷��� ������ ũ��� ��ġ.
		mpBrush							// ��(brush)
	);
}

void TextComponent::SetRect(RECT rect) noexcept
{
	mRect = rect;
}
