#include "pch.h"
#include "DevScene.h"
#include "Actor.h"
#include "Player.h"
#include "Orc.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "SpriteActor.h"
#include "Projectile.h"


DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
	// Load Soldier Texture
	ResourceManager::GetInstance()->LoadTexture(L"SoldierIdleRight", L"Soldier\\Soldier-Idle-Right.png");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierIdleLeft", L"Soldier\\Soldier-Idle-Left.png");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierMoveRight", L"Soldier\\Soldier-Walk-Right.png");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierMoveLeft", L"Soldier\\Soldier-Walk-Left.png");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierAttackRight", L"Soldier\\Soldier-Attack03-Right.png");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierAttackLeft", L"Soldier\\Soldier-Attack03-Left.png");

	// Create Soldier Flipbook
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SoldierIdleRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SoldierIdleRight");
		fb->SetInfo({ texture, L"FB_SoldierIdleRight", {100, 100}, 0, 5, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SoldierIdleLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SoldierIdleLeft");
		fb->SetInfo({ texture, L"FB_SoldierIdleLeft", {100, 100}, 0, 5, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SoldierMoveRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SoldierMoveRight");
		fb->SetInfo({ texture, L"FB_SoldierMoveRight", {100, 100}, 0, 6, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SoldierMoveLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SoldierMoveLeft");
		fb->SetInfo({ texture, L"FB_SoldierMoveLeft", {100, 100}, 0, 6, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SoldierAttackRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SoldierAttackRight");
		fb->SetInfo({ texture, L"FB_SoldierAttackRight", {100, 100}, 0, 8, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SoldierAttackLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SoldierAttackLeft");
		fb->SetInfo({ texture, L"FB_SoldierAttackLeft", {100, 100}, 0, 8, 0, 0.5f });
	}
	{
		Player* player = new Player();
		player->SetPos({ 300,300 });
		AddActor(player);
	}


	// Load Orc Texture
	ResourceManager::GetInstance()->LoadTexture(L"OrcIdle", L"Orc\\Orc-Idle.png");
	ResourceManager::GetInstance()->LoadTexture(L"OrcMove", L"Orc\\Orc-Walk.png");
	ResourceManager::GetInstance()->LoadTexture(L"OrcAttack", L"Orc\\Orc-Attack01.png");
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcIdle");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcIdle");
		fb->SetInfo({ texture, L"FB_OrcIdle", {100, 100}, 0, 5, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcMove");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcMove");
		fb->SetInfo({ texture, L"FB_OrcMove", {100, 100}, 0, 7, 0, 0.5f});
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcAttack");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcAttack");
		fb->SetInfo({ texture, L"FB_OrcAttack", {100, 100}, 0, 5, 0, 1.f});
	}
	{
		Orc* orc = new Orc();
		AddActor(orc);
	}

	// BackGround
	//ResourceManager::GetInstance()->LoadTexture(L"Tilemap01", L"Tilemap\\Tilemap03.png");
	//ResourceManager::GetInstance()->CreateSprite(L"Tilemap01", ResourceManager::GetInstance()->GetTexture(L"Tilemap01"));
	//{
	//	Sprite* sprite = ResourceManager::GetInstance()->GetSprite(L"Tilemap01");

	//	SpriteActor* background = new SpriteActor();
	//	background->SetSprite(sprite);
	//	background->SetLayer(LAYER_BACKGROUND);
	//	const Vec2Int size = sprite->GetSize();
	//	background->SetPos(Vec2(size.x / 2, size.y / 2));

	//	AddActor(background);
	//}

	ResourceManager::GetInstance()->LoadTexture(L"Arrow", L"Projectile\\Arrow01(32x32).png");
	ResourceManager::GetInstance()->CreateSprite(L"Arrow", ResourceManager::GetInstance()->GetTexture(L"Arrow"));

	Super::Init();
}

void DevScene::Update()
{	
	Super::Update();
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);

	//{
	//	Graphics graphics(hdc);
	//	Pen      pen(Color(255, 0, 0, 255));
	//	for (int32 i = 0; i <= 800 ; i += 16)
	//	{
	//		graphics.DrawLine(&pen, i, 0, i, 600);
	//	}
	//	for (int32 i = 0; i <= 600; i+=16)
	//	{
	//		graphics.DrawLine(&pen, 0, i, 800, i);
	//	}
	//}
}



//bool DevScene::CanGo(Vec2Int cellpos)
//{
//	return true;
//}
//
//Vec2 DevScene::ConvertPos(Vec2Int cellPos)
//{
//	Vec2 ret = {};
//
//	//if (_tilemapActor == nullptr)
//	//	return ret;
//
//	//Tilemap* tm = _tilemapActor->GetTilemap();
//	//if (tm == nullptr)
//	//	return ret;
//
//	//int32 size = tm->GetTileSize();
//	//Vec2 pos = _tilemapActor->GetPos();
//	// 
//	//int32 size = 16;
//	//ret.x = pos.x + cellPos.x * size + (size / 2);
//	//ret.y = pos.y + cellPos.y * size + (size / 2);
//
//
//	//ret.x = cellPos.x * size + (size / 2);
//	//ret.y = cellPos.y * size + (size / 2);
//
//	return ret;
//}
