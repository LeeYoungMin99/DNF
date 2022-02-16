#include "stdafx.h"
#include "TextComponent.h"

#include "GameObject.h"
#include "PositionComponent.h"

TextComponent::TextComponent(const wchar_t* text, const wchar_t* font, float size, D2D1::ColorF color, GameObject* owner, INT32 order)
	:Component(owner, order)
{
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(_dWriteFactory), reinterpret_cast<IUnknown**>(&_dWriteFactory));
	_dWriteFactory->CreateTextFormat(
		font,							// ��Ʈ �йи� �̸��� ���ڿ�
		NULL,							// ��Ʈ �÷��� ��ü, NULL=�ý��� ��Ʈ �÷���
		DWRITE_FONT_WEIGHT_THIN,		// ��Ʈ ����. LIGHT, NORMAL, BOLD ��.
		DWRITE_FONT_STYLE_NORMAL,		// ��Ʈ ��Ÿ��. NORMAL, OBLIQUE, ITALIC.
		DWRITE_FONT_STRETCH_NORMAL,		// ��Ʈ ����. CONDENSED, NORMAL, MEDIUM, EXTEXDED ��.
		size,							// ��Ʈ ũ��.
		L"ko",							// �������� ���ڿ��� ���.  ����-�̱�=L"en-us", �ѱ���-�ѱ�=L"ko-kr"
		&_textFormat
	);

	_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);            // ���� ���� ����
	_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);  // ���� ���� ���� ����
	_gRenderTarget->CreateSolidColorBrush(color, &_brush);
	_text = text;
}

void TextComponent::Init()
{
	_posComp = GetOwner()->GetComponent<PositionComponent>();
}

void TextComponent::Render()
{
	if (nullptr != _posComp)
	{
		RECT rect = { _rect.left	+ (LONG)_posComp->GetX(),
					  _rect.top		+ (LONG)_posComp->GetY(),
					  _rect.right	+ (LONG)_posComp->GetX(),
					  _rect.bottom	+ (LONG)_posComp->GetY()};

		WriteText(rect);
	}
	else
	{
		WriteText(_rect);
	}
}

void TextComponent::WriteText(const RECT rect)
{
	_gRenderTarget->DrawTextW(
		_text,							// WCHAR* ���ڿ�
		(UINT32)wcslen(_text),			// ������ ����
		_textFormat,					// IDWriteTextFormat �ؽ�Ʈ ���� 
		D2D1::RectF((FLOAT)rect.left, (FLOAT)rect.top, (FLOAT)rect.right, (FLOAT)rect.bottom),	// �׷��� ������ ũ��� ��ġ.
		_brush							// ��(brush)
	);
}
