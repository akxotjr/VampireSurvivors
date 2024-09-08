#pragma once
#include "Actor.h"

enum TILE_SIZE
{
	TILE_SIZEX = 16,
	TILE_SIZEY = 16,
};

class Tilemap;

class TilemapActor : public Actor
{
	using Super = Actor;
public:
	TilemapActor();
	virtual ~TilemapActor();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

protected:
	Tilemap* _tilemap = nullptr;

};

