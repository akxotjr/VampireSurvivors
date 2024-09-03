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

}

SelectSkillPanel::~SelectSkillPanel()
{
	//RemoveAllChild();
}

void SelectSkillPanel::Init()
{
	Super::Init();
}

void SelectSkillPanel::Update()
{
	Super::Update();
	if (_finished)
	{
		GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
		scene->RemoveUI(this);
		return;
	}
}

void SelectSkillPanel::Render(HDC hdc)
{
	//float deltaTime = TimeManager::GetInstance()->GetDeltaTime();

	//_sumTime += deltaTime;
	//if (_sumTime >= 3.f)
	//{
	//	//GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	//	//scene->RemmoveUI(this);
	//	return;
	//}
	
	Super::Render(hdc);
}

void SelectSkillPanel::RemoveAllChild()
{
	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	for (auto& child : _children)
	{ 
		//scene->RemoveUI(child);
		RemoveChild(child.get());
	}
	//scene->RemoveUI(this);
	//return;
}
