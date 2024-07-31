#pragma once
#include "Actor.h"

enum TILE_SIZE
{
	TILE_SIZEX = 32,
	TILE_SIZEY = 32,
};

class Tilemap;

class TilemapActor : public Actor
{
	using Super = Actor;
public:
	TilemapActor();
	virtual ~TilemapActor();

	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

protected:
	Tilemap* _tilemap = nullptr;

};

