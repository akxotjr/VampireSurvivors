#include "pch.h"
#include "GameScene.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "FlipbookActor.h"
#include "Player.h"
#include "Background.h"
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
	ResourceManager::GetInstance()->LoadTexture(L"SoldierHurtRight", L"Soldier\\Soldier-Hurt-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierHurtLeft", L"Soldier\\Soldier-Hurt-Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierDeathRight", L"Soldier\\Soldier-Death-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SoldierDeathLeft", L"Soldier\\Soldier-Death-Left.bmp");

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
	// Slash
	ResourceManager::GetInstance()->LoadTexture(L"Slash00", L"Skills\\Slash\\Skill-Slash00.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash01", L"Skills\\Slash\\Skill-Slash01.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash02", L"Skills\\Slash\\Skill-Slash02.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash03", L"Skills\\Slash\\Skill-Slash03.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash04", L"Skills\\Slash\\Skill-Slash04.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash05", L"Skills\\Slash\\Skill-Slash05.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash06", L"Skills\\Slash\\Skill-Slash06.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash07", L"Skills\\Slash\\Skill-Slash07.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash08", L"Skills\\Slash\\Skill-Slash08.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash09", L"Skills\\Slash\\Skill-Slash09.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash10", L"Skills\\Slash\\Skill-Slash10.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash11", L"Skills\\Slash\\Skill-Slash11.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash12", L"Skills\\Slash\\Skill-Slash12.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash13", L"Skills\\Slash\\Skill-Slash13.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash14", L"Skills\\Slash\\Skill-Slash14.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash15", L"Skills\\Slash\\Skill-Slash15.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash16", L"Skills\\Slash\\Skill-Slash16.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash17", L"Skills\\Slash\\Skill-Slash17.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash18", L"Skills\\Slash\\Skill-Slash18.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash19", L"Skills\\Slash\\Skill-Slash19.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash20", L"Skills\\Slash\\Skill-Slash20.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash21", L"Skills\\Slash\\Skill-Slash21.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash22", L"Skills\\Slash\\Skill-Slash22.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash23", L"Skills\\Slash\\Skill-Slash23.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash24", L"Skills\\Slash\\Skill-Slash24.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash25", L"Skills\\Slash\\Skill-Slash25.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash26", L"Skills\\Slash\\Skill-Slash26.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash27", L"Skills\\Slash\\Skill-Slash27.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash28", L"Skills\\Slash\\Skill-Slash28.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash29", L"Skills\\Slash\\Skill-Slash29.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash30", L"Skills\\Slash\\Skill-Slash30.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash31", L"Skills\\Slash\\Skill-Slash31.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash32", L"Skills\\Slash\\Skill-Slash32.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash33", L"Skills\\Slash\\Skill-Slash33.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash34", L"Skills\\Slash\\Skill-Slash34.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"Slash35", L"Skills\\Slash\\Skill-Slash35.bmp");

	ResourceManager::GetInstance()->CreateSprite(L"Slash00", ResourceManager::GetInstance()->GetTexture(L"Slash00"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash01", ResourceManager::GetInstance()->GetTexture(L"Slash01"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash02", ResourceManager::GetInstance()->GetTexture(L"Slash02"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash03", ResourceManager::GetInstance()->GetTexture(L"Slash03"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash04", ResourceManager::GetInstance()->GetTexture(L"Slash04"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash05", ResourceManager::GetInstance()->GetTexture(L"Slash05"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash06", ResourceManager::GetInstance()->GetTexture(L"Slash06"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash07", ResourceManager::GetInstance()->GetTexture(L"Slash07"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash08", ResourceManager::GetInstance()->GetTexture(L"Slash08"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash09", ResourceManager::GetInstance()->GetTexture(L"Slash09"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash10", ResourceManager::GetInstance()->GetTexture(L"Slash10"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash11", ResourceManager::GetInstance()->GetTexture(L"Slash11"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash12", ResourceManager::GetInstance()->GetTexture(L"Slash12"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash13", ResourceManager::GetInstance()->GetTexture(L"Slash13"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash14", ResourceManager::GetInstance()->GetTexture(L"Slash14"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash15", ResourceManager::GetInstance()->GetTexture(L"Slash15"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash16", ResourceManager::GetInstance()->GetTexture(L"Slash16"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash17", ResourceManager::GetInstance()->GetTexture(L"Slash17"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash18", ResourceManager::GetInstance()->GetTexture(L"Slash18"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash19", ResourceManager::GetInstance()->GetTexture(L"Slash19"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash20", ResourceManager::GetInstance()->GetTexture(L"Slash20"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash21", ResourceManager::GetInstance()->GetTexture(L"Slash21"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash22", ResourceManager::GetInstance()->GetTexture(L"Slash22"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash23", ResourceManager::GetInstance()->GetTexture(L"Slash23"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash24", ResourceManager::GetInstance()->GetTexture(L"Slash24"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash25", ResourceManager::GetInstance()->GetTexture(L"Slash25"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash26", ResourceManager::GetInstance()->GetTexture(L"Slash26"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash27", ResourceManager::GetInstance()->GetTexture(L"Slash27"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash28", ResourceManager::GetInstance()->GetTexture(L"Slash28"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash29", ResourceManager::GetInstance()->GetTexture(L"Slash29"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash30", ResourceManager::GetInstance()->GetTexture(L"Slash30"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash31", ResourceManager::GetInstance()->GetTexture(L"Slash31"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash32", ResourceManager::GetInstance()->GetTexture(L"Slash32"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash33", ResourceManager::GetInstance()->GetTexture(L"Slash33"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash34", ResourceManager::GetInstance()->GetTexture(L"Slash34"));
	ResourceManager::GetInstance()->CreateSprite(L"Slash35", ResourceManager::GetInstance()->GetTexture(L"Slash35"));

	// Iceburst
	ResourceManager::GetInstance()->LoadTexture(L"Iceburst", L"Skills\\Iceburst\\Skill-Iceburst.bmp");
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"Iceburst");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_Iceburst");
		fb->SetInfo({ texture, L"FB_Iceburst", {64, 64}, 0, 15, 0, 1.f , false});
	}

	// GravityCannon
	ResourceManager::GetInstance()->LoadTexture(L"GravityCannon", L"Skills\\GravityCannon\\Skill-GravityCannon03.bmp");
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GravityCannon");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GravityCannon");
		fb->SetInfo({ texture, L"FB_GravityCannon", {100, 80}, 0, 7, 0, 1.f});
	}

	ResourceManager::GetInstance()->LoadTexture(L"ForceField", L"Skills\\ForceField\\Skill-ForceField03.bmp");
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"ForceField");
		/*Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_ForceField");
		fb->SetInfo({ texture, L"FB_ForceField", {64, 64}, 0, 4, 0, 0.5f });*/
		ResourceManager::GetInstance()->CreateSprite(L"ForceField", texture);
	}

	ResourceManager::GetInstance()->LoadTexture(L"Lightning", L"Skills\\Lightning\\Skill-Lightning03.bmp");
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"Lightning");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_Lightning");
		fb->SetInfo({ texture, L"FB_Lightning", {128, 128}, 0, 23, 0, 2.f, false });
	}

	ResourceManager::GetInstance()->LoadTexture(L"Suriken", L"Skills\\Suriken\\Skill-Suriken.bmp");
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"Suriken");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_Suriken");
		fb->SetInfo({ texture, L"FB_Suriken", {32, 32}, 0, 7, 0, 0.5f });
	}

#pragma endregion
#pragma region Monster
	// Load Orc Texture
	ResourceManager::GetInstance()->LoadTexture(L"OrcIdleRight", L"Orc\\Orc-Idle-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcIdleLeft", L"Orc\\Orc-Idle-Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcMoveRight", L"Orc\\Orc-Walk-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcMoveLeft", L"Orc\\Orc-Walk-Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcAttackRight", L"Orc\\Orc-Attack01-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcAttackLeft", L"Orc\\Orc-Attack01-Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcHurtRight", L"Orc\\Orc-Hurt-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcHurtLeft", L"Orc\\Orc-Hurt-Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcDeathRight", L"Orc\\Orc-Death-Right.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcDeathLeft", L"Orc\\Orc-Death-Left.bmp");
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcIdleRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcIdleRight");
		fb->SetInfo({ texture, L"FB_OrcIdleRight", {100, 100}, 0, 5, 0, 0.5f });
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
	ResourceManager::GetInstance()->LoadTexture(L"EXP01", L"Items\\EXP01.bmp", RGB(255,255,255));
#pragma endregion
#pragma region Background
	ResourceManager::GetInstance()->LoadTexture(L"Tilemap03", L"Tilemap\\Tilemap03.bmp");

#pragma endregion
#pragma region Font
	ResourceManager::GetInstance()->LoadFont(L"DamageText20", L"m3x6", L"Font\\m3x6.ttf", 20);
#pragma endregion
#pragma region UI
	ResourceManager::GetInstance()->LoadTexture(L"SelectSkillButton", L"UI\\SelectSkillButton.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"SelectSkillButton", ResourceManager::GetInstance()->GetTexture(L"SelectSkillButton"));
#pragma endregion

	{
		// Player
		Player* player = new Player();
		player->SetPos({ GWinSizeX / 2, GWinSizeY / 2 });

		AddActor(player);
	}
	{
		// Background
		Background* background = new Background();

		AddActor(background);
	}
	Super::Init();
}

void GameScene::Update()
{
	Super::Update();

	MonsterRespawn();

	CollisionManager::GetInstance()->Update();
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

	std::random_device rd;
	std::mt19937 gen(rd());


	std::uniform_real_distribution<float> radius_dist(50, 300);
	float radius = radius_dist(gen);

	std::uniform_real_distribution<float> theta_dist(0.f, 2.f * PI);
	float theta = theta_dist(gen);

	Vec2 monsterPos;
	monsterPos.x = playerPos.x + radius * cos(theta);
	monsterPos.y = playerPos.y + radius * sin(theta);

	return monsterPos;
}

