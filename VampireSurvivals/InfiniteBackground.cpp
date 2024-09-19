#include "pch.h"
#include "InfiniteBackground.h"
#include "Scene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Sprite.h"

InfiniteBackground::InfiniteBackground()
{
}

InfiniteBackground::~InfiniteBackground()
{
}

void InfiniteBackground::Init()
{
	Super::Init();
}

void InfiniteBackground::Update()
{
	Super::Update();
}

void InfiniteBackground::Render(HDC hdc)
{
    Vec2 cameraPos = SceneManager::GetInstance()->GetCameraPos();

    GameScene* scene = static_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
    Vec2 playerPos = scene->GetPlayerPos();

    Vec2 startPosF = { playerPos.x - GWinSizeX / 2, playerPos.y - GWinSizeY / 2 };
    Vec2Int startTilePos = WrapPos(ConvertTilePos({ (int)startPosF.x, (int)startPosF.y }));

    float offsetX = fmodf(startPosF.x, (float)Tile_Size);
    //if (offsetX < 0) offsetX += _tileSize / 2;

    float offsetY = fmodf(startPosF.y, (float)Tile_Size);
    //if (offsetY < 0) offsetY += _tileSize / 2;


    const Vec2Int& mapSize = _sprite->GetSize();

    for (int32 y = -1; y <= _screenTileSize.y + 1; y++)
    {
        for (int32 x = -1; x <= _screenTileSize.x + 1; x++)
        {
            Vec2Int tilePos = WrapPos({ startTilePos.x + x, startTilePos.y + y });
            float screenX = ((x * Tile_Size) - offsetX);
            float screenY = ((y * Tile_Size) - offsetY);

            BitBlt(hdc, (int)screenX, (int)screenY, Tile_Size, Tile_Size, _sprite->GetDC(),
                tilePos.x * Tile_Size, tilePos.y * Tile_Size, SRCCOPY);

            //debug
            //if(_tilemap->GetTileAt(tilePos)->value != 0)
            //    Utils::DrawRect(hdc, { screenX + _tileSize / 2, screenY + _tileSize / 2}, _tileSize, _tileSize);
        }
    }
}
