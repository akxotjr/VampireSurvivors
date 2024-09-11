#include "pch.h"
#include "Map.h"
#include "ResourceManager.h"
#include "Tilemap.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "GameScene.h"

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
    _screenTileSize = ConvertTilePos({ GWinSizeX, GWinSizeY });
}

void Map::Update()
{
	Super::Update();
}

void Map::Render(HDC hdc)
{
    Vec2 cameraPos = SceneManager::GetInstance()->GetCameraPos();

    GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
    Vec2 playerPos = scene->GetPlayerPos();

    // ī�޶��� �»�� ��ǥ�� �������� ȭ�鿡 ���̴� ù Ÿ�� ��ǥ ���
    Vec2 startPosF = { playerPos.x - GWinSizeX / 2, playerPos.y - GWinSizeY / 2 };
    Vec2Int startTilePos = WrapPos(ConvertTilePos({ (int)startPosF.x, (int)startPosF.y }));

    // ���� Ÿ�ϰ��� offset (ȭ�� ��ǥ�� Ÿ�� ��ǥ ���� ����)
    float offsetX = fmodf(startPosF.x, (float)_tileSize);
    //if (offsetX < 0) offsetX += _tileSize / 2;

    float offsetY = fmodf(startPosF.y, (float)_tileSize);
    //if (offsetY < 0) offsetY += _tileSize / 2;


    const Vec2Int& mapSize = _sprite->GetSize();

    // ȭ�鿡 ���̴� Ÿ�ϵ��� ������
    for (int32 y = -1; y <= _screenTileSize.y + 1; y++)
    {
        for (int32 x = -1; x <= _screenTileSize.x + 1; x++)
        {
            // Ÿ�� ��ǥ ����
            Vec2Int tilePos = WrapPos({ startTilePos.x + x, startTilePos.y + y });

            // ȭ�鿡 Ÿ���� �׸� ��ġ ���
            float screenX = ((x * _tileSize) - offsetX);
            float screenY = ((y * _tileSize) - offsetY);


            // Ÿ�� ������
            BitBlt(hdc, (int)screenX, (int)screenY, _tileSize, _tileSize, _sprite->GetDC(),
                tilePos.x * _tileSize, tilePos.y * _tileSize, SRCCOPY);

            //debug
            if(_tilemap->GetTileAt(tilePos)->value != 0)
                Utils::DrawRect(hdc, { screenX + _tileSize / 2, screenY + _tileSize / 2}, _tileSize, _tileSize);
        }
    }
    
}




Vec2Int Map::WrapPos(Vec2Int pos)
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



Vec2Int Map::ConvertTilePos(Vec2Int pos)
{
	pos.x /= _tileSize;
	pos.y /= _tileSize;
	return pos;
}

void Map::DrawTile(HDC hdc, Vec2Int screenPos, Vec2Int pos)
{
    BitBlt(hdc,
        screenPos.x * _tileSize - _tileSize / 2,
        screenPos.y * _tileSize- _tileSize / 2,
        _tileSize,
        _tileSize,
        _sprite->GetDC(),
        pos.x * _tileSize - _tileSize / 2,
        pos.y * _tileSize - _tileSize / 2,
        SRCCOPY
    );
}

Vec2Int Map::GetPlaneOffset(Vec2 pos)
{
    Vec2Int poffset = {0,0};
    pos.x -= GWinSizeX / 2;
    pos.y -= GWinSizeY / 2;
    while (pos.x < 0)
    {
        pos.x += GWinSizeX;
        poffset.x++;
    }
    while (pos.y < 0)
    {
        pos.y += GWinSizeY;
        poffset.y++;
    }

    return poffset;
}

//Vec2 Map::GetOffset()
//{
//    
//}

