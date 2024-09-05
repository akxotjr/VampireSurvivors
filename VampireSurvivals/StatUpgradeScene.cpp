#include "pch.h"
#include "StatUpgradeScene.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "UI.h"
#include "Sprite.h"
#include "SpriteActor.h"
#include "Button.h"

StatUpgradeScene::StatUpgradeScene()
{
	ResourceManager::GetInstance()->LoadTexture(L"Stat-Upgrade", L"UI\\StatUpgradeScene\\Stat-Upgrade02.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"Stat-Upgrade", ResourceManager::GetInstance()->GetTexture(L"Stat-Upgrade"));

	ResourceManager::GetInstance()->LoadTexture(L"LobbyButtonDefaultRight", L"UI\\StatUpgradeScene\\LobbyButton_Default_Right.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"LobbyButtonDefaultRight", ResourceManager::GetInstance()->GetTexture(L"LobbyButtonDefaultRight"));
	ResourceManager::GetInstance()->LoadTexture(L"LobbyButtonClickedRight", L"UI\\StatUpgradeScene\\LobbyButton_Clicked_Right.bmp");
	ResourceManager::GetInstance()->CreateSprite(L"LobbyButtonClickedRight", ResourceManager::GetInstance()->GetTexture(L"LobbyButtonClickedRight"));

	{
		Sprite* sprite = ResourceManager::GetInstance()->GetSprite(L"Stat-Upgrade");
		unique_ptr<UI> background = make_unique<UI>();
		background->SetSprite(sprite);
		background->SetPos({0,0});

		AddUI(::move(background));
	}
	{
		Sprite* buttonDefault = ResourceManager::GetInstance()->GetSprite(L"LobbyButtonDefaultRight");
		Sprite* buttonClicked = ResourceManager::GetInstance()->GetSprite(L"LobbyButtonClickedRight");

		unique_ptr<Button> button = make_unique<Button>();
		button->SetPos({ 845, 155 });
		button->SetSprite(buttonDefault, BS_Default);
		button->SetSprite(buttonClicked, BS_Clicked);
		button->SetSprite(buttonClicked, BS_Pressed);
		button->AddOnClickDelegate(this, &StatUpgradeScene::GotoLobbyScene);

		AddUI(::move(button));
	}

	//ResourceManager::GetInstance()->LoadTexture(L"Stat-Upgrade-Button-Default", L"UI\\Stat-Upgrade-Button-Default.bmp");
	//ResourceManager::GetInstance()->LoadTexture(L"Stat-Upgrade-Button-Pressed", L"UI\\Stat-Upgrade-Button-Pressed.bmp");
	//ResourceManager::GetInstance()->LoadTexture(L"Stat-Upgrade-Button-Clicked", L"UI\\Stat-Upgrade-Button-Clicked.bmp");

	//{
	//	Sprite* button_default = ResourceManager::GetInstance()->CreateSprite(L"Stat-Upgrade-Button-Default", ResourceManager::GetInstance()->GetTexture(L"Stat-Upgrade-Button-Default"));
	//	Sprite* button_pressed = ResourceManager::GetInstance()->CreateSprite(L"Stat-Upgrade-Button-Pressed", ResourceManager::GetInstance()->GetTexture(L"Stat-Upgrade-Button-Pressed"));
	//	Sprite* button_clicked = ResourceManager::GetInstance()->CreateSprite(L"Stat-Upgrade-Button-Clicked", ResourceManager::GetInstance()->GetTexture(L"Stat-Upgrade-Button-Clicked"));

	//	unique_ptr<Button> button = make_unique<Button>();
	//	button->SetSprite(button_default, BS_Default);
	//	button->SetSprite(button_pressed, BS_Clicked);
	//	button->SetSprite(button_pressed, BS_Pressed);
	//	button->SetPos({ 366,231 });
	//	button->SetSize(button_default->GetSize());
	//	//button->AddOnClickDelegate(this, &StatUpgradeScene::AtkUpgradeButton);

	//	AddUI(::move(button));
	//}

	//ResourceManager::GetInstance()->LoadTexture(L"Stat-LevelUP-Gauge", L"UI\\Stat-LevelUP-Gauge.bmp");


	/*ResourceManager::GetInstance()->LoadFont(L"FantasyRPGtitle", L"Font\\FantasyRPGtitle (size 11).ttf");
	ResourceManager::GetInstance()->LoadFont(L"FantasyRPGtext", L"Font\\FantasyRPGtext (size 8).ttf");*/



}

StatUpgradeScene::~StatUpgradeScene()
{
}

void StatUpgradeScene::Init()
{
	Super::Init();
}

void StatUpgradeScene::Update()
{
	Super::Update();
}

void StatUpgradeScene::Render(HDC hdc)
{
	Super::Render(hdc);
	//HFONT hFont = ResourceManager::GetInstance()->GetFont(L"FantasyRPGtext");

	//if (hFont) {
	//	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
	//	SetTextColor(hdc, RGB(255, 255, 255)); // 파란색
	//	// 배경 투명도 설정
	//	SetBkMode(hdc, TRANSPARENT);
	//	// 텍스트 출력
	//	TextOut(hdc, 223, 253, L"ATK +10", 7);

	//	SelectObject(hdc, hOldFont);
	//}
	//else {
	//	MessageBox(NULL, L"폰트가 적용되지 않았습니다.", L"Error", MB_OK);
	//}
}

void StatUpgradeScene::AtkUpgradeButton()
{
	{
		Sprite * sprite = ResourceManager::GetInstance()->CreateSprite(L"Stat-LevelUP-Gauge", ResourceManager::GetInstance()->GetTexture(L"Stat-LevelUP-Gauge"));
		unique_ptr<UI> atkUpgradeGauge = make_unique<UI>();
		atkUpgradeGauge->SetSprite(sprite);
		atkUpgradeGauge->SetPos({ 224, 501 });

		AddUI(::move(atkUpgradeGauge));
	}
}

void StatUpgradeScene::GotoLobbyScene()
{
	SceneManager::GetInstance()->ChangeScene(SceneType::LobbyScene);
}

