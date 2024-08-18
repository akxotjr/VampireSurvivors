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

	void SetSize(Vec2Int size) { _size = size; }
	Vec2Int GetSize() { return _size; }

	RECT GetRect();
	bool IsMouseInRect();

	void SetSprite(Sprite* sprite) { _sprite = sprite; }

protected:
	Sprite* _sprite = nullptr;

	Vec2	_pos = {};
	Vec2Int _size = {};
};

