#pragma once
#include "SpriteActor.h"
#include "Tilemap.h"

class Background : public SpriteActor
{
	using Super = SpriteActor;
public:
	Background();
	virtual ~Background() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetTilemap(Tilemap* tm) { _tilemap = tm; }
	Tilemap* GetTilemap() { return _tilemap; }

	Vec2Int WrapPos(Vec2Int pos);
	Vec2Int ConvertTilePos(Vec2Int pos);

protected:
	Tilemap* _tilemap = nullptr;

	Vec2Int _mapTileSize = {};
	Vec2Int _screenTileSize = {60, 45};
};

