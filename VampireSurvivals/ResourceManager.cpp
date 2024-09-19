#include "pch.h"
#include "ResourceManager.h"
//#include "ResourceBase.h"
//#include "Texture.h"
//#include "Sprite.h"
//#include "Flipbook.h"

unique_ptr<ResourceManager> ResourceManager::instance = nullptr;

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path, uint32 transparent)
{
	if (_textures.find(key) != _textures.end()) return _textures[key].get();

	fs::path fullPath = _resourcePath / path;

	unique_ptr<Texture> texture = make_unique<Texture>();
	texture->LoadBmp(_hwnd, fullPath.c_str());
	texture->SetTransparent(transparent);
	_textures[key] = ::move(texture);

	return _textures[key].get();
}


Sprite* ResourceManager::CreateSprite(const wstring& key, Texture* texture, int32 x, int32 y, int32 cx, int32 cy)
{
	if (_sprites.find(key) != _sprites.end())
		return _sprites[key].get();

	if (cx == 0)
		cx = texture->GetSize().x;

	if (cy == 0)
		cy = texture->GetSize().y;

	unique_ptr<Sprite> sprite = make_unique<Sprite>(texture, x, y, cx, cy);
	_sprites[key] = ::move(sprite);

	return _sprites[key].get();
}

Flipbook* ResourceManager::CreateFlipbook(const wstring& key)
{
	if (_flipbooks.find(key) != _flipbooks.end())
		return _flipbooks[key].get();

	unique_ptr<Flipbook> fb = make_unique<Flipbook>();
	_flipbooks[key] = ::move(fb);

	return _flipbooks[key].get();
}

Font* ResourceManager::CreateTextFont(const wstring& key)
{
	if (_fonts.find(key) != _fonts.end())
		return _fonts[key].get();

	unique_ptr<Font> font = make_unique<Font>();
	_fonts[key] = ::move(font);

	return _fonts[key].get();
}

Tilemap* ResourceManager::LoadTilemap(const wstring& key, const wstring& path)
{
	if (_tilemaps.find(key) != _tilemaps.end()) return _tilemaps[key].get();

	fs::path fullPath = _resourcePath / path;

	unique_ptr<Tilemap> tilemap = make_unique<Tilemap>();
	tilemap->LoadFile(fullPath);
	_tilemaps[key] = ::move(tilemap);

	return _tilemaps[key].get();
}
