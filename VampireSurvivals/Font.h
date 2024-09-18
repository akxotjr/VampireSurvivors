#pragma once
#include "ResourceBase.h"

class Texture;

struct FontInfo
{
	Texture* texture = nullptr;
	Vec2Int size = {};
};

enum FontIndex
{
	Number = 0,
	UpperCase,
	LowerCase,
	SpecialChar,
};
 
class Font : public ResourceBase
{
public:
	Font();
	virtual ~Font();

	void SetInfo(const FontInfo& info) { _info = info; }
	FontInfo& GetInfo() { return _info; }

private:
	FontInfo _info = {};
};

