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
	ResourceManager::GetInstance()->LoadTexture(L"Soldier", L"Soldier.png");

	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(L"Soldier");
		Flipbook* fb = ResourceManager::GetInstance()->CreateFlipbook(L"FB_Soldier");
		fb->SetInfo({ texture, L"FB_Soldier", {100, 100}, 0, 8, 4, 0.5f });
	}

	{
		Player* player = new Player();
		//AddActor(player);
	}

	Super::Init();
}

void DevScene::Update()
{

}

void DevScene::Render(HDC hdc)
{
}