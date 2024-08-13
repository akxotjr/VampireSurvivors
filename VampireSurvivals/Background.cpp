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

	Sprite* sprite = ResourceManager::GetInstance()->CreateSprite(L"Tilemap03", ResourceManager::GetInstance()->GetTexture(L"Tilemap03"));
	SetSprite(sprite);

	const Vec2Int& size = sprite->GetSize();
	SetPos(Vec2(size.x / 2, size.y / 2));
}

void Background::Update()
{
	Super::Update();
}

void Background::Render(HDC hdc)
{
    Vec2 cameraPos = SceneManager::GetInstance()->GetCameraPos();
    const Vec2Int& size = _sprite->GetSize();

    float startX = -fmod(cameraPos.x, size.x);
    float startY = -fmod(cameraPos.y, size.y);

    int tilesX = (GWinSizeX / size.x) + 2;
    int tilesY = (GWinSizeY / size.y) + 2;

    for (int y = 0; y < tilesY; y++)
    {
        for (int x = 0; x < tilesX; x++)
        {
            int drawX = startX + x * size.x;
            int drawY = startY + y * size.y;

            BitBlt(hdc, drawX, drawY, size.x, size.y, _sprite->GetDC(), 0, 0, SRCCOPY);
        }
    }
}

