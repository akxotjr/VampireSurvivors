#pragma once
#include <windows.h>
#include <string>
using namespace std;

class Utils
{
public:
	static void DrawText(HDC hdc, Vec2 pos, const wstring& str);

	static void DrawRect(HDC hdc, Vec2 pos, int32 w, int32 h);
	
	static void DrawnFillRect(HDC hdc, Vec2 pos, int32 w, int32 h, COLORREF color1, COLORREF color2);

	static void DrawHP(HDC hdc, Vec2 pos, int32 w, int32 h, float curHP);

	static void DrawCircle(HDC hdc, Vec2 pos, int32 radius);

	static void DrawLine(HDC hdc, Vec2 from, Vec2 to);

	static void DrawLineColored(HDC hdc, Vec2 from, Vec2 to, COLORREF color);

	static void ReadBmp(const wstring& path);

	//static Vec2 ConvertPos(Vec2 pos);
};

