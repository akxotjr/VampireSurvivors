#include "pch.h"
#include "LobbyScene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "UI.h"
#include "Button.h"
#include "EventManager.h"


LobbyScene::LobbyScene()
{
	ResourceManager::GetInstance()->LoadTexture(L"LobbyBackground", L"UI\\LobbyScene\\LobbyBackground.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"LobbyBackground", ResourceManager::GetInstance()->GetTexture(L"LobbyBackground"));

	ResourceManager::GetInstance()->LoadTexture(L"StatUpgradeButtonDefaultRight", L"UI\\LobbyScene\\StatUpgradeButton_Default_Right.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"StatUpgradeButtonDefaultRight", ResourceManager::GetInstance()->GetTexture(L"StatUpgradeButtonDefaultRight"));
	ResourceManager::GetInstance()->LoadTexture(L"StatUpgradeButtonClickedRight", L"UI\\LobbyScene\\StatUpgradeButton_Clicked_Right.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"StatUpgradeButtonClickedRight", ResourceManager::GetInstance()->GetTexture(L"StatUpgradeButtonClickedRight"));

	ResourceManager::GetInstance()->LoadTexture(L"GameStartButtonDefault", L"UI\\LobbyScene\\GameStartButton_Default.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"GameStartButtonDefault", ResourceManager::GetInstance()->GetTexture(L"GameStartButtonDefault"));
	ResourceManager::GetInstance()->LoadTexture(L"GameStartButtonPressed", L"UI\\LobbyScene\\GameStartButton_Pressed.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"GameStartButtonPressed", ResourceManager::GetInstance()->GetTexture(L"GameStartButtonPressed"));
	ResourceManager::GetInstance()->LoadTexture(L"GameStartButtonClicked", L"UI\\LobbyScene\\GameStartButton_Clicked.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"GameStartButtonClicked", ResourceManager::GetInstance()->GetTexture(L"GameStartButtonClicked"));


	// TODO
	// map select button




	{
		Sprite* bg = ResourceManager::GetInstance()->GetSprite(L"LobbyBackground");

		unique_ptr<UI> background = make_unique<UI>();
		background->SetSprite(bg);
		background->SetPos({ 0,0 });

		AddUI(::move(background));
	}	
	{
		Sprite* buttonDefault = ResourceManager::GetInstance()->GetSprite(L"GameStartButtonDefault");
		Sprite* buttonPressed = ResourceManager::GetInstance()->GetSprite(L"GameStartButtonPressed");
		Sprite* buttonClicked = ResourceManager::GetInstance()->GetSprite(L"GameStartButtonClicked");

		unique_ptr<Button> button = make_unique<Button>();
		button->SetPos({ 550, 445 });
		button->SetSprite(buttonDefault, BS_Default);
		button->SetSprite(buttonClicked, BS_Clicked);
		button->SetSprite(buttonPressed, BS_Pressed);
		button->AddOnClickDelegate(this, &LobbyScene::GotoGameScene);

		AddUI(::move(button));
	}
	{
		Sprite* buttonDefault = ResourceManager::GetInstance()->GetSprite(L"StatUpgradeButtonDefaultRight");
		Sprite* buttonClicked = ResourceManager::GetInstance()->GetSprite(L"StatUpgradeButtonClickedRight");

		unique_ptr<Button> button = make_unique<Button>();
		button->SetPos({854, 255});
		button->SetSprite(buttonDefault, BS_Default);
		button->SetSprite(buttonClicked, BS_Clicked);
		button->SetSprite(buttonClicked, BS_Pressed);
		button->AddOnClickDelegate(this, &LobbyScene::GotoStatUpgradeScene);
		
		AddUI(::move(button));
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

void LobbyScene::GotoStatUpgradeScene()
{
	//EventManager::GetInstance()->AddEvent(SceneManager::GetInstance()->ChangeScene(SceneType::StatUpgradeScene));

	SceneManager::GetInstance()->ChangeScene(SceneType::StatUpgradeScene);
}

void LobbyScene::GotoGameScene()
{
	SceneManager::GetInstance()->ChangeScene(SceneType::GameScene);
}
