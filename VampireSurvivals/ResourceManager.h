#pragma once
#include "ResourceBase.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
// TODO : Sound

class ResourceManager
{
public:
	~ResourceManager() = default;

	static ResourceManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = make_unique<ResourceManager>();
		}
		return instance.get();
	}

	void Init(HWND hwnd, fs::path resourcePath)
	{
		_hwnd = hwnd;
		_resourcePath = resourcePath;
	}

	Texture* LoadTexture(const wstring& key, const wstring& path, uint32 transparent = RGB(0, 0, 0));
	Texture* GetTexture(const wstring& key) { return _textures[key].get(); }

	Sprite* CreateSprite(const wstring& key, Texture*, int32 x = 0, int32 y = 0, int32 cx = 0, int32 cy = 0);
	Sprite* GetSprite(const wstring& key) { return _sprites[key].get(); }

	Flipbook* CreateFlipbook(const wstring& key);
	Flipbook* GetFlipbook(const wstring& key) { return _flipbooks[key].get(); }

	HFONT LoadFont(const wstring& key, const wstring& name, const wstring& path, int32 fontSize);
	HFONT GetFont(const wstring& key) { return _fonts[key]; }

private:
	ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	friend std::unique_ptr<ResourceManager> std::make_unique<ResourceManager>();

private:
	static unique_ptr<ResourceManager> instance;

	HWND		_hwnd = {};
	fs::path	_resourcePath;

	unordered_map<wstring, unique_ptr<Texture>>		_textures;
	unordered_map<wstring, unique_ptr<Sprite>>		_sprites;
	unordered_map<wstring, unique_ptr<Flipbook>>	_flipbooks;
	//unordered_map<wstring, unique_ptr<Tilemap>>		_tilemaps;
	unordered_map<wstring, HFONT>					_fonts;
};

