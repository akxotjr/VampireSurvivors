#include "pch.h"
#include "Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

Texture* Texture::LoadBmp(HWND hwnd, const wstring& path)
{
	HDC hdc = ::GetDC(hwnd);

	_hdc = ::CreateCompatibleDC(hdc);

	_bitmap = (HBITMAP)::LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

	if (_bitmap == NULL)
	{
		::MessageBox(hwnd, path.c_str(), L"Image Load Failed", NULL);
	}

	HBITMAP prev = (HBITMAP)::SelectObject(_hdc, _bitmap);
	::DeleteObject(prev);

	BITMAP bit = {};
	::GetObject(_bitmap, sizeof(BITMAP), &bit);
	_size.x = bit.bmWidth;
	_size.y = bit.bmHeight;

	return this;
}

//Texture* Texture::LoadPng(HWND hwnd, const wstring& path)
//{
//    HDC hdc = ::GetDC(hwnd);
//
//    _hdc = ::CreateCompatibleDC(hdc);
//
//    _gdiBitmap = new Bitmap(path.c_str());
//    if (!_gdiBitmap || _gdiBitmap->GetLastStatus() != Ok) {
//        delete _gdiBitmap;
//        ::MessageBox(hwnd, path.c_str(), L"Image Load Failed", NULL);
//        //GdiplusShutdown(gdiplusToken);
//        return nullptr;
//    }
//
//    Color color(255, 0, 255); // Optional: Background color for transparency
//
//    //if (_gdiBitmap->GetHBITMAP(color, &_bitmap) != Ok) {
//    //    delete _gdiBitmap;
//    //    ::MessageBox(hwnd, L"Failed to get HBITMAP from Bitmap", L"Error", NULL);
//    //   // GdiplusShutdown(gdiplusToken);
//    //    return nullptr;
//    //}
//
//    _size.x = _gdiBitmap->GetWidth();
//    _size.y = _gdiBitmap->GetHeight();
//
//
//    //delete bitmap;
//	return this;
//}



