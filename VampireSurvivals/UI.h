#pragma once

class Sprite;

class UI
{
public:
	UI();
	virtual ~UI();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetPos(Vec2 pos) { _pos = pos; }
	Vec2 GetPos() { return _pos; }

	RECT GetRect();
	bool IsMouseInRect();

	void SetSprite(Sprite* sprite) { _sprite = sprite; }


protected:
	Sprite* _sprite = nullptr;

	Vec2	_pos = { 400, 300 };
	Vec2Int _size = { 150, 150 };
};

