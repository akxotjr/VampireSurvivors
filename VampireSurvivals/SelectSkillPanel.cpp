#include "pch.h"
#include "SelectSkillPanel.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "UI.h";
#include "Button.h"
#include "Sprite.h"
#include "Scene.h"
#include "GameScene.h"
#include "SceneManager.h"

SelectSkillPanel::SelectSkillPanel()
{
	_sprite = ResourceManager::GetInstance()->GetSprite(L"SelectSkillButton");
	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	{
		Button* button = new Button();
		button->SetSprite(_sprite, BS_Default);
		button->SetSprite(_sprite, BS_Clicked);
		button->SetSprite(_sprite, BS_Pressed);
		button->SetPos({ 245, 360 });
		button->SetSize(_sprite->GetSize());
		button->Init();
		button->AddOnClickDelegate(this, &SelectSkillPanel::RemoveAllChild);

		AddChild(button);
		scene->AddUI(button);
	}
	{
		Button* button = new Button();
		button->SetSprite(_sprite, BS_Default);
		button->SetSprite(_sprite, BS_Clicked);
		button->SetSprite(_sprite, BS_Pressed);
		button->SetPos({ 480, 360 });
		button->SetSize(_sprite->GetSize());
		button->Init();
		button->AddOnClickDelegate(this, &SelectSkillPanel::RemoveAllChild);

		AddChild(button);
		scene->AddUI(button);
	}
	{
		Button* button = new Button();
		button->SetSprite(_sprite, BS_Default);
		button->SetSprite(_sprite, BS_Clicked);
		button->SetSprite(_sprite, BS_Pressed);
		button->SetPos({ 715, 360 });
		button->SetSize(_sprite->GetSize());
		button->Init();
		button->AddOnClickDelegate(this, &SelectSkillPanel::RemoveAllChild);

		AddChild(button);
		scene->AddUI(button);
	}
}

SelectSkillPanel::~SelectSkillPanel()
{
}

void SelectSkillPanel::Init()
{
	Super::Init();
}

void SelectSkillPanel::Update()
{
	Super::Update();
}

void SelectSkillPanel::Render(HDC hdc)
{
	float deltaTime = TimeManager::GetInstance()->GetDeltaTime();

	_sumTime += deltaTime;
	if (_sumTime >= 3.f)
	{
		GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
		scene->RemmoveUI(this);
		return;
	}
	
	Super::Render(hdc);
}

void SelectSkillPanel::RemoveAllChild()
{
	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	for (auto& child : _children)
	{
		scene->RemmoveUI(child);
	}
	scene->RemmoveUI(this);
}
