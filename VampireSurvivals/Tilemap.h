#pragma once
#include "ResourceBase.h"

struct Tile
{
	int32 value = 0;
};

class Tilemap : public ResourceBase
{
	using Super = ResourceBase;
public:
	Tilemap();
	virtual ~Tilemap() override;

	virtual void LoadFile(const wstring& path) override;
	virtual void SaveFile(const wstring& path) override;

	Vec2Int GetMapSize() { return _mapSize; }
	Tile* GetTileAt(Vec2Int pos);
	vector<vector<Tile>>& GetTiles() { return _tiles; };

	void SetMapSize(Vec2Int size);

private:
	Vec2Int					_mapSize = {};
	vector<vector<Tile>>	_tiles;
};

