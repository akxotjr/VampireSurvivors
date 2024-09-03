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
	if (_sprite == nullptr) return;
	_size = _sprite->GetSize();
}

void UI::Update()
{

}

void UI::Render(HDC hdc)
{
	if (_sprite == nullptr) return;
	::TransparentBlt(hdc,
		_pos.x,
		_pos.y,
		_size.x,
		_size.y,
		_sprite->GetDC(),
		0,
		0,
		_size.x,
		_size.y,
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