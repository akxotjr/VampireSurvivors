#pragma once

class ResourceBase;
class Texture;
class Sprite;
class Flipbook;
class Tilemap;
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
	Texture* GetTexture(const wstring& key) { return _textures[key]; }

	Sprite* CreateSprite(const wstring& key, Texture* texture, int32 x = 0, int32 y = 0, int32 cx = 0, int32 cy = 0);
	Sprite* GetSprite(const wstring& key) { return _sprites[key]; }

	Flipbook* CreateFlipbook(const wstring& key);
	Flipbook* GetFlipbook(const wstring& key) { return _flipbooks[key]; }

	HFONT LoadFont(const wstring& key, const wstring& path);
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

	unordered_map<wstring, Texture*>	_textures;
	unordered_map<wstring, Sprite*>		_sprites;
	unordered_map<wstring, Flipbook*>	_flipbooks;
	unordered_map<wstring, Tilemap*>	_tilemaps;
	unordered_map<wstring, HFONT>		_fonts;
};

