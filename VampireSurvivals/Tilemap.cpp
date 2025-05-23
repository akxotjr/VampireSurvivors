#include "pch.h"
#include "Tilemap.h"
#include <iostream>
#include <fstream>

Tilemap::Tilemap()
{
}

Tilemap::~Tilemap()
{
}

void Tilemap::LoadFile(const wstring& path)
{
	ifstream ifs(path);
	string line;
	
	while (::getline(ifs, line))
	{
		vector<Tile> row;
		stringstream ss(line);
		string token;

		while (::getline(ss, token, ','))
		{
			row.push_back(Tile{::stoi(token)});
		}
		_tiles.push_back(row);
	}

	_mapSize.x = _tiles[0].size();
	_mapSize.y = _tiles.size();
}

void Tilemap::SaveFile(const wstring& path)
{

}

Tile* Tilemap::GetTileAt(Vec2Int pos)
{
	if (pos.x < 0 || pos.x >= _mapSize.x || pos.y < 0 || pos.y >= _mapSize.y)
		return nullptr;

	return &_tiles[pos.y][pos.x];
}

void Tilemap::SetMapSize(Vec2Int size)
{
	_mapSize = size;

	_tiles = vector<vector<Tile>>(size.y, vector<Tile>(size.x));

	for (int32 y = 0; y < size.y; y++)
	{
		for (int32 x = 0; x < size.x; x++)
		{
			_tiles[y][x] = Tile{ 0 };
		}
	}
}
