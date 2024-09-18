#pragma once
#include "UI.h"

class Font;

class Text : public UI
{
	using Super = UI;
public:
	Text();
	virtual ~Text();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetLetters(const string& letters) { _letters = letters; }
	void SetFont(Font* font) { _font = font; }

protected:
	string		_letters;
	Font*		_font = nullptr;
};

