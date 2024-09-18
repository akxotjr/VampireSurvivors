#include "pch.h"
#include "Text.h"
#include "Font.h"
#include "Texture.h"

Text::Text()
{
}

Text::~Text()
{
}

void Text::Init()
{
	//Super::Init();
}

void Text::Update()
{
	//Super::Update();

}

void Text::Render(HDC hdc)
{
	const FontInfo& info = _font->GetInfo();
	for (auto letter : _letters)
	{
		int32 row = 0;
		int32 col = 0;
		if (isdigit(letter))
		{
			col = FontIndex::Number;
			row = letter;
		}
		else if (isupper(letter))
		{
			col = FontIndex::UpperCase;
			row = letter - 'A';
		}
		else if (islower(letter))
		{
			col = FontIndex::LowerCase;
			row = letter - 'a';
		}
		else
		{
			col = FontIndex::SpecialChar;
		}

		TransparentBlt(
			hdc,
			(int32)_pos.x,
			(int32)_pos.y,
			info.size.x,
			info.size.y,
			info.texture->GetDC(),
			row * info.size.x,
			col * info.size.y,
			info.size.x,
			info.size.y,
			info.texture->GetTransparent()
		);
	}
}
