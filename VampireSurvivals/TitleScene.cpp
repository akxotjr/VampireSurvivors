#include "pch.h"
#include "TitleScene.h"
#include "ResourceManager.h"
#include "Button.h"
#include "SceneManager.h"

TitleScene::TitleScene()
{
	ResourceManager::GetInstance()->LoadTexture(L"TitleBackground", L"UI\\TitleBackground.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"TitleBackground", ResourceManager::GetInstance()->GetTexture(L"TitleBackground"));

	{
		Sprite* bg = ResourceManager::GetInstance()->GetSprite(L"TitleBackground");

		unique_ptr<Button> background = make_unique<Button>();
		background->SetSprite(bg, BS_Default);
		background->SetSprite(bg, BS_Clicked);
		background->SetSprite(bg, BS_Pressed);
		background->SetPos({ 0,0 });
		background->AddOnClickDelegate(this, &TitleScene::GoToLobbyScene);

		AddUI(::move(background));
	}
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	Super::Init();
}

void TitleScene::Update()
{
	Super::Update();
}

void TitleScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

void TitleScene::GoToLobbyScene()
{
	int a = 0;
	SceneManager::GetInstance()->ChangeScene(SceneType::GameScene);
}
