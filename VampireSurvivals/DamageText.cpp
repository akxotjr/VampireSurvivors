#include "pch.h"
#include "DamageText.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Scene.h"
#include "ResourceManager.h"

DamageText::DamageText()
{
}

DamageText::~DamageText()
{
}

void DamageText::Init()
{
}

void DamageText::Update()
{
	float deltaTime = TimeManager::GetInstance()->GetDeltaTime();

	_elapsedTime += deltaTime;
	if (_elapsedTime >= _lifetime)
	{
		GameScene* gamescene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
		gamescene->RemoveActor(this);
		return;
	}

	_pos.y -= deltaTime * 50.f;
}

void DamageText::Render(HDC hdc)
{
	HFONT hFont = ResourceManager::GetInstance()->GetFont(L"DamageText20");

	if (hFont)
	{
		HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);

		const Vec2& cameraPos = SceneManager::GetInstance()->GetCameraPos();

		TextOut(hdc, (int32)_pos.x - ((int32)cameraPos.x - GWinSizeX / 2), (int32)_pos.y - ((int32)cameraPos.y - GWinSizeY / 2), _text.c_str(), _text.length());

		SelectObject(hdc, hOldFont);
	}
	else
	{
		MessageBox(NULL, L"폰트가 적용되지 않았습니다.", L"Error", MB_OK);
	}
}
