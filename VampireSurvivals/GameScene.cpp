#include "pch.h"
#include "GameScene.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
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
#include "Slime.h"
#include "Cyclops.h"
#include "Goblin.h"
#include "UI.h"
#include "ResourceManager.h"
#include "Panel.h"
#include "Status.h"
#include "Button.h"
#include "Map.h"

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


	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerIdleUp", L"Player\\Swashbuckler\\Swashbuckler_Idle_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerIdleDown", L"Player\\Swashbuckler\\Swashbuckler_Idle_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerIdleLeft", L"Player\\Swashbuckler\\Swashbuckler_Idle_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerIdleRight", L"Player\\Swashbuckler\\Swashbuckler_Idle_Right.bmp");

	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerAttackUp", L"Player\\Swashbuckler\\Swashbuckler_Attack_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerAttackDown", L"Player\\Swashbuckler\\Swashbuckler_Attack_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerAttackLeft", L"Player\\Swashbuckler\\Swashbuckler_Attack_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerAttackRight", L"Player\\Swashbuckler\\Swashbuckler_Attack_Right.bmp");

	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerMoveUp", L"Player\\Swashbuckler\\Swashbuckler_Move_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerMoveDown", L"Player\\Swashbuckler\\Swashbuckler_Move_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerMoveLeft", L"Player\\Swashbuckler\\Swashbuckler_Move_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerMoveRight", L"Player\\Swashbuckler\\Swashbuckler_Move_Right.bmp");

	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerHurtUp", L"Player\\Swashbuckler\\Swashbuckler_Hurt_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerHurtDown", L"Player\\Swashbuckler\\Swashbuckler_Hurt_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerHurtLeft", L"Player\\Swashbuckler\\Swashbuckler_Hurt_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerHurtRight", L"Player\\Swashbuckler\\Swashbuckler_Hurt_Right.bmp");

	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerDeathUp", L"Player\\Swashbuckler\\Swashbuckler_Death_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerDeathDown", L"Player\\Swashbuckler\\Swashbuckler_Death_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerDeathLeft", L"Player\\Swashbuckler\\Swashbuckler_Death_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SwashbucklerDeathRight", L"Player\\Swashbuckler\\Swashbuckler_Death_Right.bmp");


	// Create Flipbook
	// Idle
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerIdleUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerIdleUp");
		fb->SetInfo({ texture, L"FB_SwashbucklerIdleUp", {48, 48}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerIdleDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerIdleDown");
		fb->SetInfo({ texture, L"FB_SwashbucklerIdleDown", {48, 48}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerIdleLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerIdleLeft");
		fb->SetInfo({ texture, L"FB_SwashbucklerIdleLeft", {48, 48}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerIdleRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerIdleRight");
		fb->SetInfo({ texture, L"FB_SwashbucklerIdleRight", {48, 48}, 0, 3, 0, 0.5f });
	}
	// Attack
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerAttackUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerAttackUp");
		fb->SetInfo({ texture, L"FB_SwashbucklerAttackUp", {48, 48}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerAttackDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerAttackDown");
		fb->SetInfo({ texture, L"FB_SwashbucklerAttackDown", {48, 48}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerAttackLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerAttackLeft");
		fb->SetInfo({ texture, L"FB_SwashbucklerAttackLeft", {48, 48}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerAttackRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerAttackRight");
		fb->SetInfo({ texture, L"FB_SwashbucklerAttackRight", {48, 48}, 0, 3, 0, 0.5f });
	}
	// Move
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerMoveUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerMoveUp");
		fb->SetInfo({ texture, L"FB_SwashbucklerMoveUp", {48, 48}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerMoveDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerMoveDown");
		fb->SetInfo({ texture, L"FB_SwashbucklerMoveDown", {48, 48}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerMoveLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerMoveLeft");
		fb->SetInfo({ texture, L"FB_SwashbucklerMoveLeft", {48, 48}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerMoveRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerMoveRight");
		fb->SetInfo({ texture, L"FB_SwashbucklerMoveRight", {48, 48}, 0, 3, 0, 0.5f });
	}
	// Hurt
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerHurtUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerHurtUp");
		fb->SetInfo({ texture, L"FB_SwashbucklerHurtUp", {48, 48}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerHurtDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerHurtDown");
		fb->SetInfo({ texture, L"FB_SwashbucklerHurtDown", {48, 48}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerHurtLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerHurtLeft");
		fb->SetInfo({ texture, L"FB_SwashbucklerHurtLeft", {48, 48}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerHurtRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerHurtRight");
		fb->SetInfo({ texture, L"FB_SwashbucklerHurtRight", {48, 48}, 0, 1, 0, 0.5f });
	}
	// Death
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerDeathUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerDeathUp");
		fb->SetInfo({ texture, L"FB_SwashbucklerDeathUp", {48, 48}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerDeathDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerDeathDown");
		fb->SetInfo({ texture, L"FB_SwashbucklerDeathDown", {48, 48}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerDeathLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerDeathLeft");
		fb->SetInfo({ texture, L"FB_SwashbucklerDeathLeft", {48, 48}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SwashbucklerDeathRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SwashbucklerDeathRight");
		fb->SetInfo({ texture, L"FB_SwashbucklerDeathRight", {48, 48}, 0, 0, 0, 0.5f });
	}

#pragma endregion 
#pragma region Skills

#pragma region Slash
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
#pragma endregion
#pragma region Iceburst
	ResourceManager::GetInstance()->LoadTexture(L"Iceburst", L"Skills\\Iceburst\\Skill-Iceburst.bmp");
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"Iceburst");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_Iceburst");
		fb->SetInfo({ texture, L"FB_Iceburst", {64, 64}, 0, 15, 0, 1.f , false});
	}
#pragma endregion 
#pragma region GravityCannon
	// GravityCannon
	ResourceManager::GetInstance()->LoadTexture(L"GravityCannon", L"Skills\\GravityCannon\\Skill-GravityCannon03.bmp");
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GravityCannon");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GravityCannon");
		fb->SetInfo({ texture, L"FB_GravityCannon", {100, 80}, 0, 7, 0, 1.f});
	}
#pragma endregion
#pragma region ForceField
	ResourceManager::GetInstance()->LoadTexture(L"ForceField01", L"Skills\\ForceField\\Skill-Forcefield01.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"ForceField02", L"Skills\\ForceField\\Skill-Forcefield02.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"ForceField03", L"Skills\\ForceField\\Skill-Forcefield03.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"ForceField04", L"Skills\\ForceField\\Skill-Forcefield04.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"ForceField05", L"Skills\\ForceField\\Skill-Forcefield05.bmp");

	ResourceManager::GetInstance()->CreateSprite(L"ForceField01", ResourceManager::GetInstance()->GetTexture(L"ForceField01"));
	ResourceManager::GetInstance()->CreateSprite(L"ForceField02", ResourceManager::GetInstance()->GetTexture(L"ForceField02"));
	ResourceManager::GetInstance()->CreateSprite(L"ForceField03", ResourceManager::GetInstance()->GetTexture(L"ForceField03"));
	ResourceManager::GetInstance()->CreateSprite(L"ForceField04", ResourceManager::GetInstance()->GetTexture(L"ForceField04"));
	ResourceManager::GetInstance()->CreateSprite(L"ForceField05", ResourceManager::GetInstance()->GetTexture(L"ForceField05"));
#pragma endregion
#pragma region Lightning
	ResourceManager::GetInstance()->LoadTexture(L"Lightning", L"Skills\\Lightning\\Skill-Lightning03.bmp");
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"Lightning");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_Lightning");
		fb->SetInfo({ texture, L"FB_Lightning", {128, 128}, 0, 23, 0, 2.f, false });
	}
#pragma endregion 
#pragma region Suriken
	ResourceManager::GetInstance()->LoadTexture(L"Suriken", L"Skills\\Suriken\\Skill-Suriken.bmp");
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"Suriken");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_Suriken");
		fb->SetInfo({ texture, L"FB_Suriken", {32, 32}, 0, 7, 0, 0.5f });
	}
#pragma endregion

#pragma endregion
#pragma region Monster

#pragma region Cyclops
	// Load Texture

	// Idle
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsIdleUp", L"Monsters\\Cyclops\\Cyclops_Idle_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsIdleDown", L"Monsters\\Cyclops\\Cyclops_Idle_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsIdleLeft", L"Monsters\\Cyclops\\Cyclops_Idle_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsIdleRight", L"Monsters\\Cyclops\\Cyclops_Idle_Right.bmp");
	// Attack
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsAttackUp", L"Monsters\\Cyclops\\Cyclops_Attack_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsAttackDown", L"Monsters\\Cyclops\\Cyclops_Attack_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsAttackLeft", L"Monsters\\Cyclops\\Cyclops_Attack_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsAttackRight", L"Monsters\\Cyclops\\Cyclops_Attack_Right.bmp");
	// Move
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsMoveUp", L"Monsters\\Cyclops\\Cyclops_Move_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsMoveDown", L"Monsters\\Cyclops\\Cyclops_Move_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsMoveLeft", L"Monsters\\Cyclops\\Cyclops_Move_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsMoveRight", L"Monsters\\Cyclops\\Cyclops_Move_Right.bmp");
	// Hurt
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsHurtUp", L"Monsters\\Cyclops\\Cyclops_Hurt_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsHurtDown", L"Monsters\\Cyclops\\Cyclops_Hurt_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsHurtLeft", L"Monsters\\Cyclops\\Cyclops_Hurt_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsHurtRight", L"Monsters\\Cyclops\\Cyclops_Hurt_Right.bmp");
	// Death
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsDeathUp", L"Monsters\\Cyclops\\Cyclops_Death_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsDeathDown", L"Monsters\\Cyclops\\Cyclops_Death_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsDeathLeft", L"Monsters\\Cyclops\\Cyclops_Death_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"CyclopsDeathRight", L"Monsters\\Cyclops\\Cyclops_Death_Right.bmp");

	// Skill
	ResourceManager::GetInstance()->LoadTexture(L"M_StoneSling", L"Monsters\\Cyclops\\Cyclops_StoneSling.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"M_StoneSling", ResourceManager::GetInstance()->GetTexture(L"M_StoneSling"));

	// Create Flipbook

	// Idle
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsIdleUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsIdleUp");
		fb->SetInfo({ texture, L"FB_CyclopsIdleUp", {32, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsIdleDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsIdleDown");
		fb->SetInfo({ texture, L"FB_CyclopsIdleDown", {32, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsIdleLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsIdleLeft");
		fb->SetInfo({ texture, L"FB_CyclopsIdleLeft", {32, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsIdleRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsIdleRight");
		fb->SetInfo({ texture, L"FB_CyclopsIdleRight", {32, 64}, 0, 3, 0, 0.5f });
	}
	// Attack
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsAttackUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsAttackUp");
		fb->SetInfo({ texture, L"FB_CyclopsAttackUp", {96, 64}, 0, 2, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsAttackDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsAttackDown");
		fb->SetInfo({ texture, L"FB_CyclopsAttackDown", {96, 64}, 0, 2, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsAttackLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsAttackLeft");
		fb->SetInfo({ texture, L"FB_CyclopsAttackLeft", {96, 64}, 0, 2, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsAttackRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsAttackRight");
		fb->SetInfo({ texture, L"FB_CyclopsAttackRight", {96, 64}, 0, 2, 0, 0.5f });
	}
	// Move
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsMoveUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsMoveUp");
		fb->SetInfo({ texture, L"FB_CyclopsMoveUp", {32, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsMoveDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsMoveDown");
		fb->SetInfo({ texture, L"FB_CyclopsMoveDown", {32, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsMoveLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsMoveLeft");
		fb->SetInfo({ texture, L"FB_CyclopsMoveLeft", {32, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsMoveRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsMoveRight");
		fb->SetInfo({ texture, L"FB_CyclopsMoveRight", {32, 64}, 0, 3, 0, 0.5f });
	}
	// Hurt
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsHurtUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsHurtUp");
		fb->SetInfo({ texture, L"FB_CyclopsHurtUp", {32, 64}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsHurtDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsHurtDown");
		fb->SetInfo({ texture, L"FB_CyclopsHurtDown", {32, 64}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsHurtLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsHurtLeft");
		fb->SetInfo({ texture, L"FB_CyclopsHurtLeft", {32, 64}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsHurtRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsHurtRight");
		fb->SetInfo({ texture, L"FB_CyclopsHurtRight", {32, 64}, 0, 1, 0, 0.5f });
	}
	// Death
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsDeathUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsDeathUp");
		fb->SetInfo({ texture, L"FB_CyclopsDeathUp", {32, 64}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsDeathDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsDeathDown");
		fb->SetInfo({ texture, L"FB_CyclopsDeathDown", {32, 64}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsDeathLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsDeathLeft");
		fb->SetInfo({ texture, L"FB_CyclopsDeathLeft", {32, 64}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"CyclopsDeathRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_CyclopsDeathRight");
		fb->SetInfo({ texture, L"FB_CyclopsDeathRight", {32, 64}, 0, 0, 0, 0.5f });
	}
#pragma endregion
#pragma region Goblin
	// Load Texture

	// Idle
	ResourceManager::GetInstance()->LoadTexture(L"GoblinIdleUp", L"Monsters\\Goblin\\Goblin_Idle_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinIdleDown", L"Monsters\\Goblin\\Goblin_Idle_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinIdleLeft", L"Monsters\\Goblin\\Goblin_Idle_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinIdleRight", L"Monsters\\Goblin\\Goblin_Idle_Right.bmp");
	// Attack									  
	ResourceManager::GetInstance()->LoadTexture(L"GoblinAttackUp", L"Monsters\\Goblin\\Goblin_Attack_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinAttackDown", L"Monsters\\Goblin\\Goblin_Attack_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinAttackLeft", L"Monsters\\Goblin\\Goblin_Attack_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinAttackRight", L"Monsters\\Goblin\\Goblin_Attack_Right.bmp");
	// Move										  
	ResourceManager::GetInstance()->LoadTexture(L"GoblinMoveUp", L"Monsters\\Goblin\\Goblin_Move_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinMoveDown", L"Monsters\\Goblin\\Goblin_Move_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinMoveLeft", L"Monsters\\Goblin\\Goblin_Move_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinMoveRight", L"Monsters\\Goblin\\Goblin_Move_Right.bmp");
	// Hurt										  
	ResourceManager::GetInstance()->LoadTexture(L"GoblinHurtUp", L"Monsters\\Goblin\\Goblin_Hurt_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinHurtDown", L"Monsters\\Goblin\\Goblin_Hurt_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinHurtLeft", L"Monsters\\Goblin\\Goblin_Hurt_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinHurtRight", L"Monsters\\Goblin\\Goblin_Hurt_Right.bmp");
	// Death									  
	ResourceManager::GetInstance()->LoadTexture(L"GoblinDeathUp", L"Monsters\\Goblin\\Goblin_Death_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinDeathDown", L"Monsters\\Goblin\\Goblin_Death_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinDeathLeft", L"Monsters\\Goblin\\Goblin_Death_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"GoblinDeathRight", L"Monsters\\Goblin\\Goblin_Death_Right.bmp");

	// Create Flipbook
	// Idle
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinIdleUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinIdleUp");
		fb->SetInfo({ texture, L"FB_GoblinIdleUp", {16, 16}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinIdleDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinIdleDown");
		fb->SetInfo({ texture, L"FB_GoblinIdleDown", {16, 16}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinIdleLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinIdleLeft");
		fb->SetInfo({ texture, L"FB_GoblinIdleLeft", {16, 16}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinIdleRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinIdleRight");
		fb->SetInfo({ texture, L"FB_GoblinIdleRight", {16, 16}, 0, 3, 0, 0.5f });
	}
	// Attack
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinAttackUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinAttackUp");
		fb->SetInfo({ texture, L"FB_GoblinAttackUp", {48, 48}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinAttackDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinAttackDown");
		fb->SetInfo({ texture, L"FB_GoblinAttackDown", {48, 48}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinAttackLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinAttackLeft");
		fb->SetInfo({ texture, L"FB_GoblinAttackLeft", {48, 48}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinAttackRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinAttackRight");
		fb->SetInfo({ texture, L"FB_GoblinAttackRight", {48, 48}, 0, 4, 0, 0.5f });
	}
	// Move
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinMoveUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinMoveUp");
		fb->SetInfo({ texture, L"FB_GoblinMoveUp", {16, 16}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinMoveDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinMoveDown");
		fb->SetInfo({ texture, L"FB_GoblinMoveDown", {16, 16}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinMoveLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinMoveLeft");
		fb->SetInfo({ texture, L"FB_GoblinMoveLeft", {16, 16}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinMoveRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinMoveRight");
		fb->SetInfo({ texture, L"FB_GoblinMoveRight", {16, 16}, 0, 3, 0, 0.5f });
	}
	// Hurt
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinHurtUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinHurtUp");
		fb->SetInfo({ texture, L"FB_GoblinHurtUp", {16, 16}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinHurtDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinHurtDown");
		fb->SetInfo({ texture, L"FB_GoblinHurtDown", {16, 16}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinHurtLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinHurtLeft");
		fb->SetInfo({ texture, L"FB_GoblinHurtLeft", {16, 16}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinHurtRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinHurtRight");
		fb->SetInfo({ texture, L"FB_GoblinHurtRight", {16, 16}, 0, 1, 0, 0.5f });
	}
	// Death
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinDeathUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinDeathUp");
		fb->SetInfo({ texture, L"FB_GoblinDeathUp", {16, 16}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinDeathDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinDeathDown");
		fb->SetInfo({ texture, L"FB_GoblinDeathDown", {16, 16}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinDeathLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinDeathLeft");
		fb->SetInfo({ texture, L"FB_GoblinDeathLeft", {16, 16}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"GoblinDeathRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_GoblinDeathRight");
		fb->SetInfo({ texture, L"FB_GoblinDeathRight", {16, 16}, 0, 0, 0, 0.5f });
	}
#pragma endregion
#pragma region Ogre
	// Load Texture

	// Idle
	ResourceManager::GetInstance()->LoadTexture(L"OgreIdleUp", L"Monsters\\Ogre\\Ogre_Idle_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OgreIdleDown", L"Monsters\\Ogre\\Ogre_Idle_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OgreIdleLeft", L"Monsters\\Ogre\\Ogre_Idle_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OgreIdleRight", L"Monsters\\Ogre\\Ogre_Idle_Right.bmp");
	// Attack									  
	ResourceManager::GetInstance()->LoadTexture(L"OgreAttackUp", L"Monsters\\Ogre\\Ogre_Attack_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OgreAttackDown", L"Monsters\\Ogre\\Ogre_Attack_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OgreAttackLeft", L"Monsters\\Ogre\\Ogre_Attack_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OgreAttackRight", L"Monsters\\Ogre\\Ogre_Attack_Right.bmp");
	// Move										  
	ResourceManager::GetInstance()->LoadTexture(L"OgreMoveUp", L"Monsters\\Ogre\\Ogre_Move_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OgreMoveDown", L"Monsters\\Ogre\\Ogre_Move_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OgreMoveLeft", L"Monsters\\Ogre\\Ogre_Move_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OgreMoveRight", L"Monsters\\Ogre\\Ogre_Move_Right.bmp");
	// Hurt										  
	ResourceManager::GetInstance()->LoadTexture(L"OgreHurtUp", L"Monsters\\Ogre\\Ogre_Hurt_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OgreHurtDown", L"Monsters\\Ogre\\Ogre_Hurt_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OgreHurtLeft", L"Monsters\\Ogre\\Ogre_Hurt_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OgreHurtRight", L"Monsters\\Ogre\\Ogre_Hurt_Right.bmp");
	// Death									  
	ResourceManager::GetInstance()->LoadTexture(L"OgreDeathUp", L"Monsters\\Ogre\\Ogre_Death_Up.bmp", RGB(255, 255, 255));
	ResourceManager::GetInstance()->LoadTexture(L"OgreDeathDown", L"Monsters\\Ogre\\Ogre_Death_Down.bmp", RGB(255, 255, 255));
	ResourceManager::GetInstance()->LoadTexture(L"OgreDeathLeft", L"Monsters\\Ogre\\Ogre_Death_Left.bmp", RGB(255, 255, 255));
	ResourceManager::GetInstance()->LoadTexture(L"OgreDeathRight", L"Monsters\\Ogre\\Ogre_Death_Right.bmp", RGB(255, 255, 255));

	// Create Flipbook
	// Idle
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreIdleUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreIdleUp");
		fb->SetInfo({ texture, L"FB_OgreIdleUp", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreIdleDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreIdleDown");
		fb->SetInfo({ texture, L"FB_OgreIdleDown", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreIdleLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreIdleLeft");
		fb->SetInfo({ texture, L"FB_OgreIdleLeft", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreIdleRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreIdleRight");
		fb->SetInfo({ texture, L"FB_OgreIdleRight", {64, 64}, 0, 3, 0, 0.5f });
	}
	// Attack
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreAttackUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreAttackUp");
		fb->SetInfo({ texture, L"FB_OgreAttackUp", {128, 128}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreAttackDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreAttackDown");
		fb->SetInfo({ texture, L"FB_OgreAttackDown", {128, 128}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreAttackLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreAttackLeft");
		fb->SetInfo({ texture, L"FB_OgreAttackLeft", {128, 128}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreAttackRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreAttackRight");
		fb->SetInfo({ texture, L"FB_OgreAttackRight", {128, 128}, 0, 4, 0, 0.5f });
	}
	// Move
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreMoveUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreMoveUp");
		fb->SetInfo({ texture, L"FB_OgreMoveUp", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreMoveDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreMoveDown");
		fb->SetInfo({ texture, L"FB_OgreMoveDown", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreMoveLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreMoveLeft");
		fb->SetInfo({ texture, L"FB_OgreMoveLeft", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreMoveRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreMoveRight");
		fb->SetInfo({ texture, L"FB_OgreMoveRight", {64, 64}, 0, 3, 0, 0.5f });
	}
	// Hurt
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreHurtUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreHurtUp");
		fb->SetInfo({ texture, L"FB_OgreHurtUp", {64, 64}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreHurtDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreHurtDown");
		fb->SetInfo({ texture, L"FB_OgreHurtDown", {64, 64}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreHurtLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreHurtLeft");
		fb->SetInfo({ texture, L"FB_OgreHurtLeft", {64, 64}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreHurtRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreHurtRight");
		fb->SetInfo({ texture, L"FB_OgreHurtRight", {64, 64}, 0, 1, 0, 0.5f });
	}
	// Death
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreDeathUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreDeathUp");
		fb->SetInfo({ texture, L"FB_OgreDeathUp", {64, 64}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreDeathDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreDeathDown");
		fb->SetInfo({ texture, L"FB_OgreDeathDown", {64, 64}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreDeathLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreDeathLeft");
		fb->SetInfo({ texture, L"FB_OgreDeathLeft", {64, 64}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OgreDeathRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OgreDeathRight");
		fb->SetInfo({ texture, L"FB_OgreDeathRight", {16, 16}, 0, 0, 0, 0.5f });
	}
#pragma endregion
#pragma region Orc
	// Load Texture

	// Idle
	ResourceManager::GetInstance()->LoadTexture(L"OrcIdleUp", L"Monsters\\Orc\\Orc_Idle_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcIdleDown", L"Monsters\\Orc\\Orc_Idle_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcIdleLeft", L"Monsters\\Orc\\Orc_Idle_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcIdleRight", L"Monsters\\Orc\\Orc_Idle_Right.bmp");
	// Attack									  
	ResourceManager::GetInstance()->LoadTexture(L"OrcAttackUp", L"Monsters\\Orc\\Orc_Attack_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcAttackDown", L"Monsters\\Orc\\Orc_Attack_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcAttackLeft", L"Monsters\\Orc\\Orc_Attack_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcAttackRight", L"Monsters\\Orc\\Orc_Attack_Right.bmp");
	// Move										  
	ResourceManager::GetInstance()->LoadTexture(L"OrcMoveUp", L"Monsters\\Orc\\Orc_Move_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcMoveDown", L"Monsters\\Orc\\Orc_Move_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcMoveLeft", L"Monsters\\Orc\\Orc_Move_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcMoveRight", L"Monsters\\Orc\\Orc_Move_Right.bmp");
	// Hurt										  
	ResourceManager::GetInstance()->LoadTexture(L"OrcHurtUp", L"Monsters\\Orc\\Orc_Hurt_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcHurtDown", L"Monsters\\Orc\\Orc_Hurt_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcHurtLeft", L"Monsters\\Orc\\Orc_Hurt_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OrcHurtRight", L"Monsters\\Orc\\Orc_Hurt_Right.bmp");
	// Death									  
	ResourceManager::GetInstance()->LoadTexture(L"OrcDeathUp", L"Monsters\\Orc\\Orc_Death_Up.bmp", RGB(255, 255, 255));
	ResourceManager::GetInstance()->LoadTexture(L"OrcDeathDown", L"Monsters\\Orc\\Orc_Death_Down.bmp", RGB(255, 255, 255));
	ResourceManager::GetInstance()->LoadTexture(L"OrcDeathLeft", L"Monsters\\Orc\\Orc_Death_Left.bmp", RGB(255, 255, 255));
	ResourceManager::GetInstance()->LoadTexture(L"OrcDeathRight", L"Monsters\\Orc\\Orc_Death_Right.bmp", RGB(255, 255, 255));

	// Create Flipbook
	// Idle
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcIdleUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcIdleUp");
		fb->SetInfo({ texture, L"FB_OrcIdleUp", {16, 24}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcIdleDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcIdleDown");
		fb->SetInfo({ texture, L"FB_OrcIdleDown", {16, 24}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcIdleLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcIdleLeft");
		fb->SetInfo({ texture, L"FB_OrcIdleLeft", {16, 24}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcIdleRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcIdleRight");
		fb->SetInfo({ texture, L"FB_OrcIdleRight", {16, 24}, 0, 3, 0, 0.5f });
	}
	// Attack
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcAttackUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcAttackUp");
		fb->SetInfo({ texture, L"FB_OrcAttackUp", {48, 56}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcAttackDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcAttackDown");
		fb->SetInfo({ texture, L"FB_OrcAttackDown", {48, 56}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcAttackLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcAttackLeft");
		fb->SetInfo({ texture, L"FB_OrcAttackLeft", {48, 56}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcAttackRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcAttackRight");
		fb->SetInfo({ texture, L"FB_OrcAttackRight", {48, 56}, 0, 4, 0, 0.5f });
	}
	// Move
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcMoveUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcMoveUp");
		fb->SetInfo({ texture, L"FB_OrcMoveUp", {16, 24}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcMoveDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcMoveDown");
		fb->SetInfo({ texture, L"FB_OrcMoveDown", {16, 24}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcMoveLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcMoveLeft");
		fb->SetInfo({ texture, L"FB_OrcMoveLeft", {16, 24}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcMoveRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcMoveRight");
		fb->SetInfo({ texture, L"FB_OrcMoveRight", {16, 24}, 0, 3, 0, 0.5f });
	}
	// Hurt
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcHurtUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcHurtUp");
		fb->SetInfo({ texture, L"FB_OrcHurtUp", {16, 24}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcHurtDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcHurtDown");
		fb->SetInfo({ texture, L"FB_OrcHurtDown", {16, 24}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcHurtLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcHurtLeft");
		fb->SetInfo({ texture, L"FB_OrcHurtLeft", {16, 24}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcHurtRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcHurtRight");
		fb->SetInfo({ texture, L"FB_OrcHurtRight", {16, 24}, 0, 1, 0, 0.5f });
	}
	// Death
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcDeathUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcDeathUp");
		fb->SetInfo({ texture, L"FB_OrcDeathUp", {16, 24}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcDeathDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcDeathDown");
		fb->SetInfo({ texture, L"FB_OrcDeathDown", {16, 24}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcDeathLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcDeathLeft");
		fb->SetInfo({ texture, L"FB_OrcDeathLeft", {16, 24}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OrcDeathRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OrcDeathRight");
		fb->SetInfo({ texture, L"FB_OrcDeathRight", {16, 24}, 0, 0, 0, 0.5f });
	}
#pragma endregion
#pragma region Slime
	// Load Texture

	// Idle
	ResourceManager::GetInstance()->LoadTexture(L"SlimeIdleUp", L"Monsters\\Slime\\Slime_Idle_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SlimeIdleDown", L"Monsters\\Slime\\Slime_Idle_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SlimeIdleLeft", L"Monsters\\Slime\\Slime_Idle_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SlimeIdleRight", L"Monsters\\Slime\\Slime_Idle_Right.bmp");
	// Attack									  
	ResourceManager::GetInstance()->LoadTexture(L"SlimeAttackUp", L"Monsters\\Slime\\Slime_Attack_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SlimeAttackDown", L"Monsters\\Slime\\Slime_Attack_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SlimeAttackLeft", L"Monsters\\Slime\\Slime_Attack_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SlimeAttackRight", L"Monsters\\Slime\\Slime_Attack_Right.bmp");
	// Move										  
	ResourceManager::GetInstance()->LoadTexture(L"SlimeMoveUp", L"Monsters\\Slime\\Slime_Move_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SlimeMoveDown", L"Monsters\\Slime\\Slime_Move_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SlimeMoveLeft", L"Monsters\\Slime\\Slime_Move_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SlimeMoveRight", L"Monsters\\Slime\\Slime_Move_Right.bmp");
	// Hurt										  
	ResourceManager::GetInstance()->LoadTexture(L"SlimeHurtUp", L"Monsters\\Slime\\Slime_Hurt_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SlimeHurtDown", L"Monsters\\Slime\\Slime_Hurt_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SlimeHurtLeft", L"Monsters\\Slime\\Slime_Hurt_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"SlimeHurtRight", L"Monsters\\Slime\\Slime_Hurt_Right.bmp");
	// Death									  
	ResourceManager::GetInstance()->LoadTexture(L"SlimeDeathUp", L"Monsters\\Slime\\Slime_Death_Up.bmp", RGB(255, 255, 255));
	ResourceManager::GetInstance()->LoadTexture(L"SlimeDeathDown", L"Monsters\\Slime\\Slime_Death_Down.bmp", RGB(255, 255, 255));
	ResourceManager::GetInstance()->LoadTexture(L"SlimeDeathLeft", L"Monsters\\Slime\\Slime_Death_Left.bmp", RGB(255, 255, 255));
	ResourceManager::GetInstance()->LoadTexture(L"SlimeDeathRight", L"Monsters\\Slime\\Slime_Death_Right.bmp", RGB(255, 255, 255));

	// Create Flipbook
	// Idle
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeIdleUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeIdleUp");
		fb->SetInfo({ texture, L"FB_SlimeIdleUp", {16, 16}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeIdleDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeIdleDown");
		fb->SetInfo({ texture, L"FB_SlimeIdleDown", {16, 16}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeIdleLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeIdleLeft");
		fb->SetInfo({ texture, L"FB_SlimeIdleLeft", {16, 16}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeIdleRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeIdleRight");
		fb->SetInfo({ texture, L"FB_SlimeIdleRight", {16, 16}, 0, 3, 0, 0.5f });
	}
	// Attack
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeAttackUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeAttackUp");
		fb->SetInfo({ texture, L"FB_SlimeAttackUp", {48, 48}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeAttackDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeAttackDown");
		fb->SetInfo({ texture, L"FB_SlimeAttackDown", {48, 48}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeAttackLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeAttackLeft");
		fb->SetInfo({ texture, L"FB_SlimeAttackLeft", {48, 48}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeAttackRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeAttackRight");
		fb->SetInfo({ texture, L"FB_SlimeAttackRight", {48, 48}, 0, 4, 0, 0.5f });
	}
	// Move
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeMoveUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeMoveUp");
		fb->SetInfo({ texture, L"FB_SlimeMoveUp", {16, 16}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeMoveDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeMoveDown");
		fb->SetInfo({ texture, L"FB_SlimeMoveDown", {16, 16}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeMoveLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeMoveLeft");
		fb->SetInfo({ texture, L"FB_SlimeMoveLeft", {16, 16}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeMoveRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeMoveRight");
		fb->SetInfo({ texture, L"FB_SlimeMoveRight", {16, 16}, 0, 3, 0, 0.5f });
	}
	// Hurt
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeHurtUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeHurtUp");
		fb->SetInfo({ texture, L"FB_SlimeHurtUp", {16, 16}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeHurtDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeHurtDown");
		fb->SetInfo({ texture, L"FB_SlimeHurtDown", {16, 16}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeHurtLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeHurtLeft");
		fb->SetInfo({ texture, L"FB_SlimeHurtLeft", {16, 16}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeHurtRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeHurtRight");
		fb->SetInfo({ texture, L"FB_SlimeHurtRight", {16, 16}, 0, 1, 0, 0.5f });
	}
	// Death
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeDeathUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeDeathUp");
		fb->SetInfo({ texture, L"FB_SlimeDeathUp", {16, 16}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeDeathDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeDeathDown");
		fb->SetInfo({ texture, L"FB_SlimeDeathDown", {16, 16}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeDeathLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeDeathLeft");
		fb->SetInfo({ texture, L"FB_SlimeDeathLeft", {16, 16}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"SlimeDeathRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_SlimeDeathRight");
		fb->SetInfo({ texture, L"FB_SlimeDeathRight", {16, 16}, 0, 0, 0, 0.5f });
	}
#pragma endregion
#pragma region WolfRider
	// Load Texture

	// Idle
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderIdleUp", L"Monsters\\WolfRider\\WolfRider_Idle_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderIdleDown", L"Monsters\\WolfRider\\WolfRider_Idle_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderIdleLeft", L"Monsters\\WolfRider\\WolfRider_Idle_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderIdleRight", L"Monsters\\WolfRider\\WolfRider_Idle_Right.bmp");
	// Attack									  
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderAttackUp", L"Monsters\\WolfRider\\WolfRider_Attack_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderAttackDown", L"Monsters\\WolfRider\\WolfRider_Attack_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderAttackLeft", L"Monsters\\WolfRider\\WolfRider_Attack_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderAttackRight", L"Monsters\\WolfRider\\WolfRider_Attack_Right.bmp");
	// Move										  
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderMoveUp", L"Monsters\\WolfRider\\WolfRider_Move_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderMoveDown", L"Monsters\\WolfRider\\WolfRider_Move_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderMoveLeft", L"Monsters\\WolfRider\\WolfRider_Move_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderMoveRight", L"Monsters\\WolfRider\\WolfRider_Move_Right.bmp");
	// Hurt										  
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderHurtUp", L"Monsters\\WolfRider\\WolfRider_Hurt_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderHurtDown", L"Monsters\\WolfRider\\WolfRider_Hurt_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderHurtLeft", L"Monsters\\WolfRider\\WolfRider_Hurt_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderHurtRight", L"Monsters\\WolfRider\\WolfRider_Hurt_Right.bmp");
	// Death									  
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderDeathUp", L"Monsters\\WolfRider\\WolfRider_Death_Up.bmp", RGB(255, 255, 255));
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderDeathDown", L"Monsters\\WolfRider\\WolfRider_Death_Down.bmp", RGB(255, 255, 255));
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderDeathLeft", L"Monsters\\WolfRider\\WolfRider_Death_Left.bmp", RGB(255, 255, 255));
	ResourceManager::GetInstance()->LoadTexture(L"WolfRiderDeathRight", L"Monsters\\WolfRider\\WolfRider_Death_Right.bmp", RGB(255, 255, 255));

	// Create Flipbook
	// Idle
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderIdleUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderIdleUp");
		fb->SetInfo({ texture, L"FB_WolfRiderIdleUp", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderIdleDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderIdleDown");
		fb->SetInfo({ texture, L"FB_WolfRiderIdleDown", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderIdleLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderIdleLeft");
		fb->SetInfo({ texture, L"FB_WolfRiderIdleLeft", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderIdleRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderIdleRight");
		fb->SetInfo({ texture, L"FB_WolfRiderIdleRight", {64, 64}, 0, 3, 0, 0.5f });
	}
	// Attack
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderAttackUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderAttackUp");
		fb->SetInfo({ texture, L"FB_WolfRiderAttackUp", {128, 128}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderAttackDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderAttackDown");
		fb->SetInfo({ texture, L"FB_WolfRiderAttackDown", {128, 128}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderAttackLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderAttackLeft");
		fb->SetInfo({ texture, L"FB_WolfRiderAttackLeft", {128, 128}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderAttackRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderAttackRight");
		fb->SetInfo({ texture, L"FB_WolfRiderAttackRight", {128, 128}, 0, 4, 0, 0.5f });
	}
	// Move
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderMoveUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderMoveUp");
		fb->SetInfo({ texture, L"FB_WolfRiderMoveUp", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderMoveDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderMoveDown");
		fb->SetInfo({ texture, L"FB_WolfRiderMoveDown", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderMoveLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderMoveLeft");
		fb->SetInfo({ texture, L"FB_WolfRiderMoveLeft", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderMoveRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderMoveRight");
		fb->SetInfo({ texture, L"FB_WolfRiderMoveRight", {64, 64}, 0, 3, 0, 0.5f });
	}
	// Hurt
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderHurtUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderHurtUp");
		fb->SetInfo({ texture, L"FB_WolfRiderHurtUp", {64, 64}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderHurtDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderHurtDown");
		fb->SetInfo({ texture, L"FB_WolfRiderHurtDown", {64, 64}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderHurtLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderHurtLeft");
		fb->SetInfo({ texture, L"FB_WolfRiderHurtLeft", {64, 64}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderHurtRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderHurtRight");
		fb->SetInfo({ texture, L"FB_WolfRiderHurtRight", {64, 64}, 0, 1, 0, 0.5f });
	}
	// Death
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderDeathUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderDeathUp");
		fb->SetInfo({ texture, L"FB_WolfRiderDeathUp", {64, 64}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderDeathDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderDeathDown");
		fb->SetInfo({ texture, L"FB_WolfRiderDeathDown", {64, 64}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderDeathLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderDeathLeft");
		fb->SetInfo({ texture, L"FB_WolfRiderDeathLeft", {64, 64}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"WolfRiderDeathRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_WolfRiderDeathRight");
		fb->SetInfo({ texture, L"FB_WolfRiderDeathRight", {16, 16}, 0, 0, 0, 0.5f });
	}
#pragma endregion
#pragma region Owlbear
	// Load Texture

	// Idle
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearIdleUp", L"Monsters\\Owlbear\\Owlbear_Idle_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearIdleDown", L"Monsters\\Owlbear\\Owlbear_Idle_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearIdleLeft", L"Monsters\\Owlbear\\Owlbear_Idle_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearIdleRight", L"Monsters\\Owlbear\\Owlbear_Idle_Right.bmp");
	// Attack									  
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearAttackUp", L"Monsters\\Owlbear\\Owlbear_Attack_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearAttackDown", L"Monsters\\Owlbear\\Owlbear_Attack_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearAttackLeft", L"Monsters\\Owlbear\\Owlbear_Attack_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearAttackRight", L"Monsters\\Owlbear\\Owlbear_Attack_Right.bmp");
	// Move										  
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearMoveUp", L"Monsters\\Owlbear\\Owlbear_Move_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearMoveDown", L"Monsters\\Owlbear\\Owlbear_Move_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearMoveLeft", L"Monsters\\Owlbear\\Owlbear_Move_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearMoveRight", L"Monsters\\Owlbear\\Owlbear_Move_Right.bmp");
	// Hurt										  
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearHurtUp", L"Monsters\\Owlbear\\Owlbear_Hurt_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearHurtDown", L"Monsters\\Owlbear\\Owlbear_Hurt_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearHurtLeft", L"Monsters\\Owlbear\\Owlbear_Hurt_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearHurtRight", L"Monsters\\Owlbear\\Owlbear_Hurt_Right.bmp");
	// Death									  
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearDeathUp", L"Monsters\\Owlbear\\Owlbear_Death_Up.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearDeathDown", L"Monsters\\Owlbear\\Owlbear_Death_Down.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearDeathLeft", L"Monsters\\Owlbear\\Owlbear_Death_Left.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"OwlbearDeathRight", L"Monsters\\Owlbear\\Owlbear_Death_Right.bmp");

	// Create Flipbook
	// Idle
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearIdleUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearIdleUp");
		fb->SetInfo({ texture, L"FB_OwlbearIdleUp", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearIdleDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearIdleDown");
		fb->SetInfo({ texture, L"FB_OwlbearIdleDown", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearIdleLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearIdleLeft");
		fb->SetInfo({ texture, L"FB_OwlbearIdleLeft", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearIdleRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearIdleRight");
		fb->SetInfo({ texture, L"FB_OwlbearIdleRight", {64, 64}, 0, 3, 0, 0.5f });
	}
	// Attack
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearAttackUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearAttackUp");
		fb->SetInfo({ texture, L"FB_OwlbearAttackUp", {128, 128}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearAttackDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearAttackDown");
		fb->SetInfo({ texture, L"FB_OwlbearAttackDown", {128, 128}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearAttackLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearAttackLeft");
		fb->SetInfo({ texture, L"FB_OwlbearAttackLeft", {128, 128}, 0, 4, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearAttackRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearAttackRight");
		fb->SetInfo({ texture, L"FB_OwlbearAttackRight", {128, 128}, 0, 4, 0, 0.5f });
	}
	// Move
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearMoveUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearMoveUp");
		fb->SetInfo({ texture, L"FB_OwlbearMoveUp", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearMoveDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearMoveDown");
		fb->SetInfo({ texture, L"FB_OwlbearMoveDown", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearMoveLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearMoveLeft");
		fb->SetInfo({ texture, L"FB_OwlbearMoveLeft", {64, 64}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearMoveRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearMoveRight");
		fb->SetInfo({ texture, L"FB_OwlbearMoveRight", {64, 64}, 0, 3, 0, 0.5f });
	}
	// Hurt
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearHurtUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearHurtUp");
		fb->SetInfo({ texture, L"FB_OwlbearHurtUp", {64, 64}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearHurtDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearHurtDown");
		fb->SetInfo({ texture, L"FB_OwlbearHurtDown", {64, 64}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearHurtLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearHurtLeft");
		fb->SetInfo({ texture, L"FB_OwlbearHurtLeft", {64, 64}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearHurtRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearHurtRight");
		fb->SetInfo({ texture, L"FB_OwlbearHurtRight", {64, 64}, 0, 1, 0, 0.5f });
	}
	// Death
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearDeathUp");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearDeathUp");
		fb->SetInfo({ texture, L"FB_OwlbearDeathUp", {64, 64}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearDeathDown");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearDeathDown");
		fb->SetInfo({ texture, L"FB_OwlbearDeathDown", {64, 64}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearDeathLeft");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearDeathLeft");
		fb->SetInfo({ texture, L"FB_OwlbearDeathLeft", {64, 64}, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"OwlbearDeathRight");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_OwlbearDeathRight");
		fb->SetInfo({ texture, L"FB_OwlbearDeathRight", {16, 16}, 0, 0, 0, 0.5f });
	}
#pragma endregion

#pragma endregion	
#pragma region Item
	ResourceManager::GetInstance()->LoadTexture(L"EXP01", L"Items\\EXP01.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"EXP02", L"Items\\EXP02.bmp");
	ResourceManager::GetInstance()->LoadTexture(L"EXP03", L"Items\\EXP03.bmp");
#pragma endregion
#pragma region Background
	ResourceManager::GetInstance()->LoadTexture(L"Tilemap03", L"Tilemap\\Tilemap03.bmp");
	//ResourceManager::GetInstance()->LoadTexture(L"Tilemap01", L"Tilemap\\Tilemap01.bmp");
	ResourceManager::GetInstance()->LoadTilemap(L"Tilemap01", L"Tilemap\\Tilemap01.txt");
#pragma endregion
#pragma region Font
	ResourceManager::GetInstance()->LoadFont(L"DamageText20", L"m3x6", L"Font\\m3x6.ttf", 20);
#pragma endregion
#pragma region UI
	ResourceManager::GetInstance()->LoadTexture(L"SelectSkillButton", L"UI\\SelectSkillButton.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"SelectSkillButton", ResourceManager::GetInstance()->GetTexture(L"SelectSkillButton"));

	// test
	ResourceManager::GetInstance()->LoadTexture(L"InGameStatus", L"UI\\InGame-Status.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"InGameStatus", ResourceManager::GetInstance()->GetTexture(L"InGameStatus"));

	// test
	ResourceManager::GetInstance()->LoadTexture(L"SlashSkillIcon36", L"UI\\Skill_UI\\Skill_Icon_36_Slash.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"SlashSkillIcon36", ResourceManager::GetInstance()->GetTexture(L"SlashSkillIcon36"));
	ResourceManager::GetInstance()->LoadTexture(L"IceburstSkillIcon36", L"UI\\Skill_UI\\Skill_Icon_36_Iceburst.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"IceburstSkillIcon36", ResourceManager::GetInstance()->GetTexture(L"IceburstSkillIcon36"));
	ResourceManager::GetInstance()->LoadTexture(L"LightningSkillIcon36", L"UI\\Skill_UI\\Skill_Icon_36_Lightning.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"LightningSkillIcon36", ResourceManager::GetInstance()->GetTexture(L"LightningSkillIcon36"));
	ResourceManager::GetInstance()->LoadTexture(L"SurikenSkillIcon36", L"UI\\Skill_UI\\Skill_Icon_36_Suriken.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"SurikenSkillIcon36", ResourceManager::GetInstance()->GetTexture(L"SurikenSkillIcon36"));
	ResourceManager::GetInstance()->LoadTexture(L"ForceFieldSkillIcon36", L"UI\\Skill_UI\\Skill_Icon_36_ForceField.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"ForceFieldSkillIcon36", ResourceManager::GetInstance()->GetTexture(L"ForceFieldSkillIcon36"));

	ResourceManager::GetInstance()->LoadTexture(L"SlashSkillIcon48", L"UI\\Skill_UI\\Skill_Icon_48_Slash.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"SlashSkillIcon48", ResourceManager::GetInstance()->GetTexture(L"SlashSkillIcon48"));
	ResourceManager::GetInstance()->LoadTexture(L"IceburstSkillIcon48", L"UI\\Skill_UI\\Skill_Icon_48_Iceburst.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"IceburstSkillIcon48", ResourceManager::GetInstance()->GetTexture(L"IceburstSkillIcon48"));
	ResourceManager::GetInstance()->LoadTexture(L"LightningSkillIcon48", L"UI\\Skill_UI\\Skill_Icon_48_Lightning.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"LightningSkillIcon48", ResourceManager::GetInstance()->GetTexture(L"LightningSkillIcon48"));
	ResourceManager::GetInstance()->LoadTexture(L"SurikenSkillIcon48", L"UI\\Skill_UI\\Skill_Icon_48_Suriken.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"SurikenSkillIcon48", ResourceManager::GetInstance()->GetTexture(L"SurikenSkillIcon48"));
	ResourceManager::GetInstance()->LoadTexture(L"ForceFieldSkillIcon48", L"UI\\Skill_UI\\Skill_Icon_48_ForceField.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"ForceFieldSkillIcon48", ResourceManager::GetInstance()->GetTexture(L"ForceFieldSkillIcon48"));

	ResourceManager::GetInstance()->LoadTexture(L"SlashSkillName", L"UI\\Skill_UI\\Skill_Name_Slash.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"SlashSkillName", ResourceManager::GetInstance()->GetTexture(L"SlashSkillName"));
	ResourceManager::GetInstance()->LoadTexture(L"IceburstSkillName", L"UI\\Skill_UI\\Skill_Name_Iceburst.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"IceburstSkillName", ResourceManager::GetInstance()->GetTexture(L"IceburstSkillName"));
	ResourceManager::GetInstance()->LoadTexture(L"LightningSkillName", L"UI\\Skill_UI\\Skill_Name_Lightning.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"LightningSkillName", ResourceManager::GetInstance()->GetTexture(L"LightningSkillName"));
	ResourceManager::GetInstance()->LoadTexture(L"SurikenSkillName", L"UI\\Skill_UI\\Skill_Name_Suriken.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"SurikenSkillName", ResourceManager::GetInstance()->GetTexture(L"SurikenSkillName"));
	ResourceManager::GetInstance()->LoadTexture(L"ForceFieldSkillName", L"UI\\Skill_UI\\Skill_Name_ForceField.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"ForceFieldSkillName", ResourceManager::GetInstance()->GetTexture(L"ForceFieldSkillName"));

	ResourceManager::GetInstance()->LoadTexture(L"HPbar", L"UI\\Status_HPbar.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"HPbar", ResourceManager::GetInstance()->GetTexture(L"HPbar"));

	ResourceManager::GetInstance()->LoadTexture(L"EXPbar", L"UI\\Status_EXPbar.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"EXPbar", ResourceManager::GetInstance()->GetTexture(L"EXPbar"));

	ResourceManager::GetInstance()->LoadTexture(L"LevelToken", L"UI\\Skill_UI\\Skill_Level_Token.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"LevelToken", ResourceManager::GetInstance()->GetTexture(L"LevelToken"));

	ResourceManager::GetInstance()->LoadTexture(L"SettingsButtonDefault", L"UI\\SettingsButton_Default.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"SettingsButtonDefault", ResourceManager::GetInstance()->GetTexture(L"SettingsButtonDefault"));
	ResourceManager::GetInstance()->LoadTexture(L"SettingsButtonClicked", L"UI\\SettingsButton_Clicked.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"SettingsButtonClicked", ResourceManager::GetInstance()->GetTexture(L"SettingsButtonClicked"));

	ResourceManager::GetInstance()->LoadTexture(L"CoinBar", L"UI\\CoinBar.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"CoinBar", ResourceManager::GetInstance()->GetTexture(L"CoinBar"));

#pragma endregion

	{
		unique_ptr<Player> player = make_unique<Player>();
		player->SetPos({ GWinSizeX / 2, GWinSizeY / 2 });
		AddActor(::move(player));
	}
	{
		// Background
		unique_ptr<Background> background = make_unique<Background>();
		AddActor(::move(background));
	}
	{
		unique_ptr<Status> ingamestatus = make_unique<Status>();
		AddUI(::move(ingamestatus));
	}
	{
		Sprite* buttonDefault = ResourceManager::GetInstance()->GetSprite(L"SettingsButtonDefault");
		Sprite* buttonClicked = ResourceManager::GetInstance()->GetSprite(L"SettingsButtonClicked");
		unique_ptr<Button> button = make_unique<Button>();
		button->SetPos({913, 0});
		button->SetSprite(buttonDefault, BS_Default);
		button->SetSprite(buttonClicked, BS_Clicked);
		button->SetSprite(buttonClicked, BS_Pressed);
		//button->AddOnClickDelegate();

		AddUI(::move(button));
	}
	{
		Sprite* sprite = ResourceManager::GetInstance()->GetSprite(L"CoinBar");
		unique_ptr<UI> bar = make_unique<UI>();
		bar->SetPos({ 817, 0 });
		bar->SetSprite(sprite);

		AddUI(::move(bar));
	}

	//test
	{
		unique_ptr<Map> map = make_unique<Map>();
		
	}
	Super::Init();
}

void GameScene::Update()
{
	Super::Update();

	HandleWave();

	CollisionManager::GetInstance()->Update();
}

void GameScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

Vec2 GameScene::MonsterRandomPos()
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
void GameScene::HandleWave()
{
	float deltaTime = TimeManager::GetInstance()->GetAdjustDeltaTime();
	_sumTime += deltaTime;
	_spawnSumTime += deltaTime;

	if (_spawnSumTime >= _spawnCoolTime)
	{
		if (_sumTime < 20.f)
		{
			MonsterBuilder[(int32)MonsterID::ID_Slime]();
			_spawnCoolTime -= 0.1f;
		}
		else if (_sumTime < 120.f)
		{
			if (_sumTime > 60.f && !_firstEpicMonster)
			{
				MonsterBuilder[(int32)MonsterID::ID_Owlbear]();
				_firstEpicMonster = true;
			}
			MonsterBuilder[(int32)MonsterID::ID_Slime]();
			MonsterBuilder[(int32)MonsterID::ID_Goblin]();
		}
		else if (_sumTime < 180.f)
		{
			MonsterBuilder[(int32)MonsterID::ID_Slime]();
			MonsterBuilder[(int32)MonsterID::ID_Goblin]();
			MonsterBuilder[(int32)MonsterID::ID_Orc]();
		}
		else if (_sumTime < 240.f)
		{
			for (int32 i = 0; i < 2; i++)
			{
				MonsterBuilder[(int32)MonsterID::ID_Goblin]();
				MonsterBuilder[(int32)MonsterID::ID_Orc]();
			}
			MonsterBuilder[(int32)MonsterID::ID_Cyclops]();
		}
		else if (_sumTime < 300.f)
		{
			MonsterBuilder[(int32)MonsterID::ID_Slime]();
			MonsterBuilder[(int32)MonsterID::ID_Orc]();
			MonsterBuilder[(int32)MonsterID::ID_WolfRider]();
		}
		else if (_sumTime < 420.f)
		{
			if (_sumTime > 300.f && !_secondEpicMonster)
			{
				MonsterBuilder[(int32)MonsterID::ID_Ogre]();
			}
			MonsterBuilder[(int32)MonsterID::ID_Orc]();
			MonsterBuilder[(int32)MonsterID::ID_Goblin]();
			MonsterBuilder[(int32)MonsterID::ID_WolfRider]();
		}
		else if (_sumTime < 480.f)
		{
			for (int32 i = 0; i < 2; i++)
			{
				MonsterBuilder[(int32)MonsterID::ID_Orc]();
				MonsterBuilder[(int32)MonsterID::ID_Goblin]();
				MonsterBuilder[(int32)MonsterID::ID_WolfRider]();
			}
			MonsterBuilder[(int32)MonsterID::ID_Cyclops]();
		}
		else if (_sumTime <= 600.f)
		{
			MonsterBuilder[(int32)MonsterID::ID_Slime]();
			MonsterBuilder[(int32)MonsterID::ID_Orc]();
			MonsterBuilder[(int32)MonsterID::ID_Goblin]();
			MonsterBuilder[(int32)MonsterID::ID_WolfRider](); 
			MonsterBuilder[(int32)MonsterID::ID_Cyclops]();
		}
		_spawnSumTime = 0.f;
	}
}


