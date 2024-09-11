#pragma once
#include "SpriteActor.h"

class Sprite;
class Tilemap;

class Map : public SpriteActor
{
	using Super = SpriteActor;
public:
	Map();
	virtual ~Map() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	Vec2Int WrapPos(Vec2Int pos);
	Vec2Int ConvertTilePos(Vec2Int pos);

	Tilemap* GetTilemap() { return _tilemap; }

	void DrawTile(HDC hdc, Vec2Int screenPos, Vec2Int pos);

	Vec2 GetOffset() { return _offset; }
	Vec2Int GetPlaneOffset(Vec2 pos);

protected:
	Tilemap*	_tilemap = nullptr;
	//Sprite*		_sprite = nullptr;
	int32		_tileSize = 16;
	Vec2Int		_mapTileSize = {};
	Vec2Int		_screenTileSize = {};

	Vec2Int		_startTilePos = {};

	Vec2		_offset = {};
};

