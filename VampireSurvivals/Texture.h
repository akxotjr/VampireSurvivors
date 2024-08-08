#pragma once

#include "ResourceBase.h"

class Texture : public ResourceBase
{
public:
	Texture();
	virtual ~Texture();

	Texture*	LoadBmp(HWND hwnd, const wstring& path);
	Texture*	LoadPng(HWND hwnd, const wstring& path);
	HDC			GetDC() { return _hdc; }

	void		SetSize(Vec2Int size) { _size = size; }	
	Vec2Int		GetSize() { return _size; }

	void		SetTransparent(uint32 transparent) { _transparent = transparent; }
	uint32		GetTransparent() { return _transparent; }
	
	Bitmap*		GetGdiBitmap() { return _gdiBitmap; }

private:
	HDC			_hdc = {};
	HBITMAP		_bitmap = {};
	Vec2Int		_size = {};
	uint32		_transparent = RGB(0, 0, 0);
	Bitmap*		_gdiBitmap = nullptr;
};

