#include "pch.h"
#include "Map.h"
#include "ResourceManager.h"
#include "Tilemap.h"
#include "Sprite.h"


Map::Map()
{
	_tilemap = ResourceManager::GetInstance()->GetTilemap(L"Tilemap01");
	_tilemap->SetTileSize(16);
	int a = 0;
}

Map::~Map()
{
}

void Map::Init()
{
	Super::Init();
}

void Map::Update()
{
	Super::Update();
}

void Map::Render(HDC hdc)
{
	Super::Render(hdc);
}
