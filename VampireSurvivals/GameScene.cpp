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
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"


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
	ResourceManager::GetInstance()->LoadTexture(L"SoldierIdleRight", L"Soldier\\Soldier-Idle-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierIdleLeft", L"Soldier\\Soldier-Idle-Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierMoveRight", L"Soldier\\Soldier-Walk-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierMoveLeft", L"Soldier\\Soldier-Walk-Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierAttackRight", L"Soldier\\Soldier-Attack03-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierAttackLeft", L"Soldier\\Soldier-Attack03-Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierHurt", L"Soldier\\Soldier-Hurt-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierHurt", L"Soldier\\Soldier-Hurt-Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierDeath", L"Soldier\\Soldier-Death-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierDeath", L"Soldier\\Soldier-Death-Left.bmp");

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
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SoldierHurtRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SoldierHurtRight");
		fb->SetInfo({ texture, L"FB_SoldierHurtRight", {100, 100}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SoldierHurtLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SoldierHurtLeft");
		fb->SetInfo({ texture, L"FB_SoldierHurtLeft", {100, 100}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SoldierDeathRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SoldierDeathRight");
		fb->SetInfo({ texture, L"FB_SoldierDeathRight", {100, 100}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SoldierDeathLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SoldierDeathLeft");
		fb->SetInfo({ texture, L"FB_SoldierDeathLeft", {100, 100}, 0, 3, 0, 0.5f });
	}

#pragma endregion 
#pragma region Skills
	ResourceManager::GetInstance()->LoadTexture(L"Arrow", L"Projectile\\Arrow01(32x32).png");
	ResourceManager::GetInstance()->CreateSprite(L"Arrow", ResourceManager::GetInstance()->GetTexture(L"Arrow"));
#pragma endregion
#pragma region Monster
	// Load Orc Texture
	ResourceManager::GetInstance()->LoadTexture(L"OrcIdle", L"Orc\\Orc-Idle-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcIdleLeft", L"Orc\\Orc-Idle-Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcMoveRight", L"Orc\\Orc-Walk-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcMoveLeft", L"Orc\\Orc-Walk-Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcAttackRight", L"Orc\\Orc-Attack01-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcAttackLeft", L"Orc\\Orc-Attack01-Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcHurt", L"Orc\\Orc-Hurt-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcHurt", L"Orc\\Orc-Hurt-Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcDeath", L"Orc\\Orc-Death-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcDeath", L"Orc\\Orc-Death-Left.bmp");
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcIdle");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcIdle");
		fb->SetInfo({ texture, L"FB_OrcIdle", {100, 100}, 0, 5, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcIdleLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcIdleLeft");
		fb->SetInfo({ texture, L"FB_OrcIdleLeft", {100, 100}, 0, 5, 0, 0.5f });
	}
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
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcHurtRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcHurtRight");
		fb->SetInfo({ texture, L"FB_OrcHurtRight", {100, 100}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcHurtLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcHurtLeft");
		fb->SetInfo({ texture, L"FB_OrcHurtLeft", {100, 100}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcDeathRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcDeathRight");
		fb->SetInfo({ texture, L"FB_OrcDeathRight", {100, 100}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcDeathLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcDeathLeft");
		fb->SetInfo({ texture, L"FB_OrcDeathLeft", {100, 100}, 0, 3, 0, 0.5f });
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

