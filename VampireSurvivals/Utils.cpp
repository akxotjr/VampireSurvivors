#include "pch.h"
#include "Utils.h"

void Utils::DrawText(HDC hdc, Vec2 pos, const wstring& str)
{
	::TextOut(hdc, static_cast<int32>(pos.x), static_cast<int32>(pos.y), str.c_str(), static_cast<int32>(str.size()));
}

void Utils::DrawRect(HDC hdc, Vec2 pos, int32 w, int32 h)
{
	::Rectangle(hdc, static_cast<int32>(pos.x - w / 2), static_cast<int32>(pos.y - h / 2), static_cast<int32>(pos.x + w / 2), static_cast<int32>(pos.y + h / 2));
}

void Utils::DrawnFillRect(HDC hdc, Vec2 pos, int32 w, int32 h, COLORREF color1, COLORREF color2)
{
	RECT outerRect = {
			static_cast<int32>(pos.x - w / 2), 
			static_cast<int32>(pos.y - h / 2), 
			static_cast<int32>(pos.x + w / 2), 
			static_cast<int32>(pos.y + h / 2)
	}; 
	RECT innerRect = { outerRect.left + 1, outerRect.top + 1, outerRect.right - 1, outerRect.bottom - 1 }; 

	HPEN pen = ::CreatePen(PS_SOLID, 1, color1);
	HPEN oldPen = (HPEN)::SelectObject(hdc, (HGDIOBJ)pen);
	HBRUSH emptyBrush = (HBRUSH)::GetStockObject(NULL_BRUSH); 
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, (HGDIOBJ)emptyBrush);
	::Rectangle(hdc, outerRect.left, outerRect.top, outerRect.right, outerRect.bottom);

	HBRUSH brush = ::CreateSolidBrush(color2);
	::FillRect(hdc, &innerRect, brush);

	::SelectObject(hdc, (HGDIOBJ)oldPen);
	::SelectObject(hdc, (HGDIOBJ)oldBrush);
	::DeleteObject(pen);
	::DeleteObject(brush);
}

void Utils::DrawHP(HDC hdc, Vec2 pos, int32 w, int32 h, float curHP)
{
	RECT outerRect = {
		static_cast<int32>(pos.x - w / 2),
		static_cast<int32>(pos.y - h / 2),
		static_cast<int32>(pos.x + w / 2),
		static_cast<int32>(pos.y + h / 2)
	};
	RECT innerRect = { outerRect.left + 1, outerRect.top + 1, outerRect.left + static_cast<int32>(w * curHP) - 1, outerRect.bottom - 1};

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(0,0,0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, (HGDIOBJ)pen);
	HBRUSH emptyBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, (HGDIOBJ)emptyBrush);
	::Rectangle(hdc, outerRect.left, outerRect.top, outerRect.right, outerRect.bottom);

	HBRUSH brush = ::CreateSolidBrush(RGB(255,0,0));
	::FillRect(hdc, &innerRect, brush);

	::SelectObject(hdc, (HGDIOBJ)oldPen);
	::SelectObject(hdc, (HGDIOBJ)oldBrush);
	::DeleteObject(pen);
	::DeleteObject(brush);
}

void Utils::DrawCircle(HDC hdc, Vec2 pos, int32 radius)
{
	::Ellipse(hdc, static_cast<int32>(pos.x - radius), static_cast<int32>(pos.y - radius), static_cast<int32>(pos.x + radius), static_cast<int32>(pos.y + radius));
}

void Utils::DrawLine(HDC hdc, Vec2 from, Vec2 to)
{
	::MoveToEx(hdc, static_cast<int32>(from.x), static_cast<int32>(from.y), nullptr);
	::LineTo(hdc, static_cast<int32>(to.x), static_cast<int32>(to.y));
}

void Utils::DrawLineColored(HDC hdc, Vec2 from, Vec2 to, COLORREF color)
{
	HPEN pen = ::CreatePen(PS_SOLID, 1, color);
	HPEN oldPen = (HPEN)::SelectObject(hdc, (HGDIOBJ)pen);

	::MoveToEx(hdc, static_cast<int32>(from.x), static_cast<int32>(from.y), nullptr);
	::LineTo(hdc, static_cast<int32>(to.x), static_cast<int32>(to.y));

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}

void Utils::ReadBmp(const wstring& path)
{
	FILE* fp = nullptr;

	if (::_wfopen_s(&fp, path.c_str(), L"rb") != 0)
		return;

	BITMAPFILEHEADER fileHeader = {};
	::fread_s(&fileHeader, sizeof(fileHeader), sizeof(fileHeader), 1, fp);

	BITMAPINFOHEADER infoHeader = {};
	::fread_s(&infoHeader, sizeof(infoHeader), sizeof(infoHeader), 1, fp);

	int32 imgSize = infoHeader.biWidth * infoHeader.biHeight * 4;
	char* buffer = (char*)::malloc(imgSize);
	fread_s(buffer, imgSize, imgSize, 1, fp);

	//::free(buffer);
}


