#include "pch.h"
#include "LobbyScene.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "UI.h"


LobbyScene::LobbyScene()
{
	ResourceManager::GetInstance()->LoadTexture(L"LobbyBackground", L"UI\\LobbyBackground.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"LobbyBackground", ResourceManager::GetInstance()->GetTexture(L"LobbyBackground"));

	// 
	// map select button
	// game start button
	// go to statupgrade butoon



	{
		Sprite* bg = ResourceManager::GetInstance()->GetSprite(L"LobbyBackground");

		unique_ptr<UI> background = make_unique<UI>();
		background->SetSprite(bg);
		background->SetPos({ 0,0 });

		AddUI(::move(background));
	}
}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Init()
{
	Super::Init();
}

void LobbyScene::Update()
{
	Super::Update();
}

void LobbyScene::Render(HDC hdc)
{
	Super::Render(hdc);
}
