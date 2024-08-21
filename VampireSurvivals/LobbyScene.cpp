#include "pch.h"
#include "LobbyScene.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"


LobbyScene::LobbyScene()
{
}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Init()
{
	//ResourceManager::GetInstance()->LoadTexture(L"Stat-Upgrade", L"UI\\Stat-Upgrade.bmp");
	//ResourceManager::GetInstance()->LoadTexture(L"Stat-LevelUP-Gauge", L"UI\\Stat-LevelUp-Gauge.bmp");

	//ResourceManager::GetInstance()->LoadFont(L"FantasyRPGtitle", L"Font\\FantasyRPGtitle (size 11).ttf");
	//ResourceManager::GetInstance()->LoadFont(L"FantasyRPGtext", L"Font\\FantasyRPGtext (size 8).ttf");

	Super::Init();
}

void LobbyScene::Update()
{
	Super::Update();
}

void LobbyScene::Render(HDC hdc)
{
	Super::Render(hdc);

	//{
	//	Sprite* sprite = ResourceManager::GetInstance()->CreateSprite(L"Stat-Upgrade", ResourceManager::GetInstance()->GetTexture(L"Stat-Upgrade"));
	//	::TransparentBlt(hdc, 0, 0, GWinSizeX, GWinSizeY, sprite->GetDC(),
	//		0,
	//		0,
	//		sprite->GetSize().x,
	//		sprite->GetSize().y,
	//		sprite->GetTransparent());
	//}

	{
		Sprite* sprite = ResourceManager::GetInstance()->CreateSprite(L"Stat-LevelUP-Gauge", ResourceManager::GetInstance()->GetTexture(L"Stat-LevelUP-Gauge"));
		::TransparentBlt(hdc, 224, 219 , sprite->GetSize().x, sprite->GetSize().y, sprite->GetDC(),
			0,
			0,
			sprite->GetSize().x,
			sprite->GetSize().y,
			sprite->GetTransparent());
	}
	{
		Sprite* sprite = ResourceManager::GetInstance()->CreateSprite(L"Stat-LevelUP-Gauge", ResourceManager::GetInstance()->GetTexture(L"Stat-LevelUP-Gauge"));
		::TransparentBlt(hdc, 234, 219, sprite->GetSize().x, sprite->GetSize().y, sprite->GetDC(),
			0,
			0,
			sprite->GetSize().x,
			sprite->GetSize().y,
			sprite->GetTransparent());
	}

	{
		HFONT hFont = ResourceManager::GetInstance()->GetFont(L"FantasyRPGtitle");

		if (hFont) {
			HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

			// ���� ���� ����
			//SetTextColor(hdc, RGB(0, 0, 255)); // �Ķ���

			// ��� ���� ����
			//SetBkMode(hdc, TRANSPARENT);

			// �ؽ�Ʈ ���
			TextOut(hdc, 20, 20, L"asdfasdfasdf",12);

			SelectObject(hdc, hOldFont);
		}
		else {
			MessageBox(NULL, L"��Ʈ�� ������� �ʾҽ��ϴ�.", L"Error", MB_OK);
		}
	}
	
}
