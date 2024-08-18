#include "pch.h"
#include "ResourceManager.h"
#include "ResourceBase.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"

unique_ptr<ResourceManager> ResourceManager::instance = nullptr;

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path, uint32 transparent)
{
	if (_textures.find(key) != _textures.end()) return _textures[key];

	fs::path fullPath = _resourcePath / path;

	Texture* texture = new Texture();
	texture->LoadBmp(_hwnd, fullPath.c_str());
	//texture->LoadPng(_hwnd, fullPath.c_str());
	texture->SetTransparent(transparent);
	_textures[key] = texture;

	return texture;
}


Sprite* ResourceManager::CreateSprite(const wstring& key, Texture* texture, int32 x, int32 y, int32 cx, int32 cy)
{
	if (_sprites.find(key) != _sprites.end())
		return _sprites[key];

	if (cx == 0)
		cx = texture->GetSize().x;

	if (cy == 0)
		cy = texture->GetSize().y;

	Sprite* sprite = new Sprite(texture, x, y, cx, cy);
	_sprites[key] = sprite;

	return sprite;
}

Flipbook* ResourceManager::CreateFlipbook(const wstring& key)
{
	if (_flipbooks.find(key) != _flipbooks.end())
		return _flipbooks[key];

	Flipbook* fb = new Flipbook();
	_flipbooks[key] = fb;

	return fb;
}

HFONT ResourceManager::LoadFont(const wstring& key, const wstring& path)
{
	if (_fonts.find(key) != _fonts.end())
		return _fonts[key];

	fs::path fullPath = _resourcePath / path;

	HFONT hfont = {};

	if (AddFontResource(fullPath.c_str()) > 0)
	{
		// 폰트 생성 (추가한 폰트의 이름을 사용)
		hfont = CreateFont(
			20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, key.c_str()
		);

		if (!hfont) {
			MessageBox(NULL, L"폰트 생성에 실패했습니다.", L"Error", MB_OK);
		}
	}

	_fonts[key] = hfont;

	return _fonts[key];
}
