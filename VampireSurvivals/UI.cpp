#include "pch.h"
#include "UI.h"
#include "InputManager.h"
#include "Sprite.h"

UI::UI()
{

}

UI::~UI()
{

}

void UI::Init()
{

}

void UI::Update()
{

}

void UI::Render(HDC hdc)
{
	if (_sprite == nullptr) return;
	Vec2Int size = _sprite->GetSize();
	::TransparentBlt(hdc,
		_pos.x - size.x / 2,
		_pos.y - size.y / 2,
		size.x, 
		size.y, 
		_sprite->GetDC(),
		0,
		0,
		size.x,
		size.y,
		_sprite->GetTransparent());
}

RECT UI::GetRect()
{
	RECT rect =
	{
		_pos.x - _size.x / 2,
		_pos.y - _size.y / 2,
		_pos.x + _size.x / 2,
		_pos.y + _size.y / 2
	};

	return rect;
}

bool UI::IsMouseInRect()
{
	RECT rect = GetRect();

	POINT mousePos = InputManager::GetInstance()->GetMousePos();

	//return ::PtInRect(&rect, mousePos);
	if (mousePos.x < rect.left)
		return false;
	if (mousePos.x > rect.right)
		return false;
	if (mousePos.y < rect.top)
		return false;
	if (mousePos.y > rect.bottom)
		return false;

	return true;
}