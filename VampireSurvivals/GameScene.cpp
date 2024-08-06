#include "pch.h"
#include "GameScene.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "FlipbookActor.h"
#include "Player.h"
#include "Monster.h"


GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
#pragma region Player
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
#pragma endregion 
#pragma region Skills
	ResourceManager::GetInstance()->LoadTexture(L"Arrow", L"Projectile\\Arrow01(32x32).png");
	ResourceManager::GetInstance()->CreateSprite(L"Arrow", ResourceManager::GetInstance()->GetTexture(L"Arrow"));
#pragma endregion
#pragma region Monster
	// Load Orc Texture
	ResourceManager::GetInstance()->LoadTexture(L"OrcIdle", L"Orc\\Orc-Idle.png");
	//ResourceManager::GetInstance()->LoadTexture(L"OrcIdleLeft", L"Orc\\Orc-Idle-Left.png");
	ResourceManager::GetInstance()->LoadTexture(L"OrcMoveRight", L"Orc\\Orc-Walk-Right.png");
	ResourceManager::GetInstance()->LoadTexture(L"OrcMoveLeft", L"Orc\\Orc-Walk-Left.png");
	ResourceManager::GetInstance()->LoadTexture(L"OrcAttackRight", L"Orc\\Orc-Attack01-Right.png");
	ResourceManager::GetInstance()->LoadTexture(L"OrcAttackLeft", L"Orc\\Orc-Attack01-Left.png");
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcIdle");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcIdle");
		fb->SetInfo({ texture, L"FB_OrcIdle", {100, 100}, 0, 5, 0, 0.5f });
	}
	//{
	//	Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcIdleLeft");
	//	Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcIdleLeft");
	//	fb->SetInfo({ texture, L"FB_OrcIdleLeft", {100, 100}, 0, 5, 0, 0.5f });
	//}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcMoveRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcMoveRight");
		fb->SetInfo({ texture, L"FB_OrcMoveRight", {100, 100}, 0, 7, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcMoveLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcMoveLeft");
		fb->SetInfo({ texture, L"FB_OrcMoveLeft", {100, 100}, 0, 7, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcAttackRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcAttackRight");
		fb->SetInfo({ texture, L"FB_OrcAttackRight", {100, 100}, 0, 5, 0, 1.f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcAttackLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcAttackLeft");
		fb->SetInfo({ texture, L"FB_OrcAttackLeft", {100, 100}, 0, 5, 0, 1.f });
	}
#pragma endregion	
#pragma region Item

#pragma endregion
#pragma region Background
#pragma endregion


	{
		Player* player = new Player();
		// TODO : player setPos (mapsize/2)
		player->SetPos({ 480, 360 });
		AddActor(player);
	}
	{
		// TODO : Background
	}
	Super::Init();
}

void GameScene::Update()
{
	Super::Update();

	MonsterRespawn();
}

void GameScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

void GameScene::MonsterRespawn()
{
	float deltaTime = TimeManager::GetInstance()->GetDeltaTime();

	_sumTime += deltaTime;
	if (_sumTime >= _coolTime)
	{
		// new monster
		Monster* monster = new Monster();
		monster->SetPos(MonsterRandomPos(deltaTime));
		AddActor(monster);


		_sumTime = 0.f;
	}
}

Vec2 GameScene::MonsterRandomPos(float deltaTime)
{
	Vec2 playerPos = GetPlayerPos();

	srand(deltaTime);

	int min = 30;
	int max = 100;
	int radius = min + rand() % (max - min + 1);

	float theta = ((float)rand() / RAND_MAX) * 2 * PI;

	Vec2 monsterPos;
	monsterPos.x = playerPos.x + radius * cos(theta);
	monsterPos.y = playerPos.y + radius * sin(theta);

	return monsterPos;
}
