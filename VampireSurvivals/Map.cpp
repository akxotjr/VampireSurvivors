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

    // ī�޶��� �»�� ��ǥ�� �������� ȭ�鿡 ���̴� ù Ÿ�� ��ǥ ���
    Vec2 startPosF = { cameraPos.x - GWinSizeX / 2, cameraPos.y - GWinSizeY / 2 };
    Vec2Int startTilePos = WrapPos(ConvertTilePos({ (int)startPosF.x, (int)startPosF.y }));

    // ���� Ÿ�ϰ��� offset (ȭ�� ��ǥ�� Ÿ�� ��ǥ ���� ����)
    float offsetX = startPosF.x - (startTilePos.x * _tileSize);
    float offsetY = startPosF.y - (startTilePos.y * _tileSize);

    const Vec2Int& mapSize = _sprite->GetSize();

    // ȭ�鿡 ���̴� Ÿ�ϵ��� ������
    for (int32 y = 0; y <= _viewTileSize.y; y++)
    {
        for (int32 x = 0; x <= _viewTileSize.x; x++)
        {
            // Ÿ�� ��ǥ ����
            Vec2Int tilePos = { (startTilePos.x + x) % _mapTileSize.x, (startTilePos.y + y) % _mapTileSize.y };

            // ȭ�鿡 Ÿ���� �׸� ��ġ ���
            float screenX = (x * _tileSize) - offsetX;
            float screenY = (y * _tileSize) - offsetY;

            // Ÿ�� ������
            BitBlt(hdc, (int)screenX, (int)screenY, _tileSize, _tileSize, _sprite->GetDC(),
                tilePos.x * _tileSize, tilePos.y * _tileSize, SRCCOPY);
        }
    }
}




Vec2Int Map::WrapPos(Vec2Int pos)
{
    Vec2Int wpos;
    wpos.x = ((pos.x % _mapTileSize.x) + _mapTileSize.x) % _mapTileSize.x;
    wpos.y = ((pos.y % _mapTileSize.y) + _mapTileSize.y) % _mapTileSize.y;
    return wpos;
}



Vec2Int Map::ConvertTilePos(Vec2Int pos)
{
	pos.x /= _tileSize;
	pos.y /= _tileSize;
	return pos;
}
