#include "pch.h"
#include "Background.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Sprite.h"

Background::Background()
{
}

Background::~Background()
{
}

void Background::Init()
{
	Super::Init();
	SetLayer(LAYER_TYPE::LAYER_BACKGROUND);

	if (_sprite == nullptr) return;
	const Vec2Int& size = _sprite->GetSize();
	SetPos(Vec2(size.x / 2, size.y / 2));

	_mapTileSize = ConvertTilePos(size);
}

void Background::Update()
{
	Super::Update();
}

void Background::Render(HDC hdc)
{
	Super::Render(hdc);
}

Vec2Int Background::WrapPos(Vec2Int pos)
{
    Vec2Int wpos;
    while (pos.x < 0)
    {
        pos.x += _mapTileSize.x;
    }
    while (pos.y < 0)
    {
        pos.y += _mapTileSize.y;
    }

    wpos.x = pos.x % _mapTileSize.x;
    wpos.y = pos.y % _mapTileSize.y;
    return wpos;
}

Vec2Int Background::ConvertTilePos(Vec2Int pos)
{
    pos.x /= Tile_Size;
    pos.y /= Tile_Size;
    return pos;
}

