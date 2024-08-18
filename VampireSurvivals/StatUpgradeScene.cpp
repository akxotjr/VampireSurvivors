#include "pch.h"
#include "StatUpgradeScene.h"
#include "ResourceManager.h"
#include "UI.h"
#include "Sprite.h"
#include "SpriteActor.h"
#include "Button.h"

StatUpgradeScene::StatUpgradeScene()
{
	ResourceManager::GetInstance()->LoadTexture(L"Stat-Upgrade", L"UI\\Stat-Upgrade.bmp");

	{
		Sprite* sprite = ResourceManager::GetInstance()->CreateSprite(L"Stat-Upgrade", ResourceManager::GetInstance()->GetTexture(L"Stat-Upgrade"));
		UI* background = new UI();
		background->SetSprite(sprite);
		background->SetPos(Vec2(sprite->GetSize().x, sprite->GetSize().y));

		AddUI(background);
	}

	ResourceManager::GetInstance()->LoadTexture(L"Stat-Upgrade-Button", L"UI\\Stat-Upgrade-button.bmp");

	{
		Sprite* sprite = ResourceManager::GetInstance()->CreateSprite(L"Stat-Upgrade-Button", ResourceManager::GetInstance()->GetTexture(L"Stat-Upgrade-Button"));
		Button* button = new Button();
		button->SetSprite(sprite, BS_Default);
		button->SetSprite(sprite, BS_Clicked);
		button->SetSprite(sprite, BS_Pressed);
		button->SetPos({ 384,233 });

		button->AddOnClickDelegate(this, &StatUpgradeScene::AtkUpgradeButton);

		AddUI(button);
	}

	ResourceManager::GetInstance()->LoadTexture(L"Stat-LevelUP-Gauge", L"UI\\Stat-LevelUP-Gauge.bmp");

	ResourceManager::GetInstance()->LoadFont(L"m3x6", L"Font\\m3x6.ttf");
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

	{
		HFONT hFont = ResourceManager::GetInstance()->GetFont(L"m3x6");

		if (hFont) {
			HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

			// 글자 색상 설정
			//SetTextColor(hdc, RGB(0, 0, 255)); // 파란색

			// 배경 투명도 설정
			//SetBkMode(hdc, TRANSPARENT);

			// 텍스트 출력
			TextOut(hdc, 20, 20, L"asdfasdfasdf", 12);

			SelectObject(hdc, hOldFont);
		}
		else {
			MessageBox(NULL, L"폰트가 적용되지 않았습니다.", L"Error", MB_OK);
		}
	}
}

void StatUpgradeScene::AtkUpgradeButton()
{
	{
		Sprite * sprite = ResourceManager::GetInstance()->CreateSprite(L"Stat-LevelUP-Gauge", ResourceManager::GetInstance()->GetTexture(L"Stat-LevelUP-Gauge"));
		UI* atkUpgradeGauge = new UI();
		atkUpgradeGauge->SetSprite(sprite);
		atkUpgradeGauge->SetPos({ 224, 501 });

		AddUI(atkUpgradeGauge);
	}
}

