#include "pch.h"
#include "DevScene.h"
#include "Actor.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
	ResourceManager::GetInstance()->LoadTexture(L"SoldierIdle", L"Soldier\\PlayerDown.bmp");
	//ResourceManager::GetInstance()->LoadTexture(L"SoldierMove", L"Soldier\\Soldier-Walk.png");
	//ResourceManager::GetInstance()->LoadTexture(L"SoldierAttack", L"Soldier\\Soldier-Attack03.png");
	//ResourceManager::GetInstance()->LoadTexture(L"P")
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SoldierIdle");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SoldierIdle");
		fb->SetInfo({ texture, L"FB_SoldierIdle", {100, 100}, 0, 5, 0, 0.5f });
	}
	//{
	//	Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SoldierMove");
	//	Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SoldierMove");
	//	fb->SetInfo({ texture, L"FB_SoldierMove", {100, 100}, 0, 6, 0, 0.5f });
	//}
	//{
	//	Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SoldierAttack");
	//	Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SoldierAttack");
	//	fb->SetInfo({ texture, L"FB_SoldierAttack", {100, 100}, 0, 8, 0, 0.5f });
	//}

	{
		Player* player = new Player();
		AddActor(player);
	}

	Super::Init();
}

void DevScene::Update()
{
	Super::Update();
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);

}

bool DevScene::CanGo(Vec2Int cellpos)
{
	return true;
}

Vec2 DevScene::ConvertPos(Vec2Int cellPos)
{
	Vec2 ret = {};

	//if (_tilemapActor == nullptr)
	//	return ret;

	//Tilemap* tm = _tilemapActor->GetTilemap();
	//if (tm == nullptr)
	//	return ret;

	//int32 size = tm->GetTileSize();
	//Vec2 pos = _tilemapActor->GetPos();
	// 
	//int32 size = 16;
	//ret.x = pos.x + cellPos.x * size + (size / 2);
	//ret.y = pos.y + cellPos.y * size + (size / 2);


	//ret.x = cellPos.x * size + (size / 2);
	//ret.y = cellPos.y * size + (size / 2);

	return ret;
}
