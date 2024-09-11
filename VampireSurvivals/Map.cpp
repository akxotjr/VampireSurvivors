#include "pch.h"
#include "Map.h"
#include "ResourceManager.h"
#include "Tilemap.h"
#include "Sprite.h"
#include "SceneManager.h"


Map::Map()
{
	_tilemap = ResourceManager::GetInstance()->GetTilemap(L"Tilemap01");
	_tilemap->SetTileSize(_tileSize);
}

Map::~Map()
{
}

void Map::Init()
{
	Super::Init();
	const Vec2Int& size = _sprite->GetSize();
	SetPos(Vec2(size.x / 2, size.y / 2));

	_mapTileSize = ConvertTilePos(size);
    _viewTileSize = ConvertTilePos({ GWinSizeX, GWinSizeY });
    
    
}

void Map::Update()
{
	Super::Update();
}

void Map::Render(HDC hdc)
{
    Vec2 cameraPos = SceneManager::GetInstance()->GetCameraPos();

    Vec2 startPosF = { cameraPos.x - GWinSizeX / 2, cameraPos.y - GWinSizeY / 2 };
    Vec2Int startTilePos = WrapPos(ConvertTilePos({ (int)startPosF.x, (int)startPosF.y }));

    float offsetX = fmodf(startPosF.x, (float)_tileSize);
    float offsetY = fmodf(startPosF.y, (float)_tileSize);

    //if (offsetX < 0) offsetX += _tileSize;
    //if (offsetY < 0) offsetY += _tileSize;

    const Vec2Int& mapSize = _sprite->GetSize();

    for (int32 y = -1; y <= _viewTileSize.y; y++)
    {
        for (int32 x = -1; x <= _viewTileSize.x; x++)
        {
            Vec2Int tilePos = { (startTilePos.x + x) % _mapTileSize.x, (startTilePos.y + y) % _mapTileSize.y };

            float screenX = ((x * _tileSize) - offsetX);
            float screenY = ((y * _tileSize) - offsetY);

            BitBlt(hdc, (int)screenX, (int)screenY, _tileSize, _tileSize, _sprite->GetDC(),
                tilePos.x * _tileSize, tilePos.y * _tileSize, SRCCOPY);
        }
    }
}



Vec2Int Map::WrapPos(Vec2Int pos)
{
    Vec2Int wpos;
    const Vec2Int& size = _sprite->GetSize();  // 타일맵의 크기

    // x, y 좌표를 타일맵 경계를 넘어가면 wrap 시키기
    wpos.x = (pos.x + size.x) % size.x;
    wpos.y = (pos.y + size.y) % size.y;

    return wpos;  // 타일 좌표 반환
}


Vec2Int Map::ConvertTilePos(Vec2Int pos)
{
	pos.x /= _tileSize;
	pos.y /= _tileSize;
	return pos;
}
