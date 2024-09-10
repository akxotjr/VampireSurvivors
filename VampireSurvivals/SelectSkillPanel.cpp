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
	_skillButton = ResourceManager::GetInstance()->GetSprite(L"SelectSkillButton");

	_skillIcon[SkillID::ID_Slash] = ResourceManager::GetInstance()->GetSprite(L"SlashSkillIcon48");
	_skillIcon[SkillID::ID_Iceburst] = ResourceManager::GetInstance()->GetSprite(L"IceburstSkillIcon48");
	_skillIcon[SkillID::ID_Lightning] = ResourceManager::GetInstance()->GetSprite(L"LightningSkillIcon48");
	_skillIcon[SkillID::ID_Suriken] = ResourceManager::GetInstance()->GetSprite(L"SurikenSkillIcon48");
	_skillIcon[SkillID::ID_ForceField] = ResourceManager::GetInstance()->GetSprite(L"ForceFieldSkillIcon48");

	_skillName[SkillID::ID_Slash] = ResourceManager::GetInstance()->GetSprite(L"SlashSkillName");
	_skillName[SkillID::ID_Iceburst] = ResourceManager::GetInstance()->GetSprite(L"IceburstSkillName");
	_skillName[SkillID::ID_Lightning] = ResourceManager::GetInstance()->GetSprite(L"LightningSkillName");
	_skillName[SkillID::ID_Suriken] = ResourceManager::GetInstance()->GetSprite(L"SurikenSkillName");
	_skillName[SkillID::ID_ForceField] = ResourceManager::GetInstance()->GetSprite(L"ForceFieldSkillName");

}

SelectSkillPanel::~SelectSkillPanel()
{
}

void SelectSkillPanel::Init()
{
	Super::Init();

	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	_player = scene->GetPlayer();
	pair<int32, int32> temp = _player->RandomSkill();
	int32 skills = temp.first;
	_buttonCount = temp.second;
	
	int32 buttonIdx = 0;
	for (int32 i = 0; i < SkillID::ID_Count; i++)
	{
		if (skills & (1 << i))
		{
			SkillID id = (SkillID)i;

			unique_ptr<Button> button = make_unique<Button>();
			button->SetPos(_buttonPos[_buttonCount - 1][buttonIdx]);
			button->SetSprite(_skillButton, BS_Default);
			button->SetSprite(_skillButton, BS_Clicked);
			button->SetSprite(_skillButton, BS_Pressed);
			button->AddOnClickDelegate(_player, &Player::SkillLevelUP, id, this);
			button->Init();

			AddChild(::move(button));
			
			unique_ptr<UI> icon = make_unique<UI>();
			icon->SetSprite(_skillIcon[id]);
			icon->SetPos({ _buttonPos[_buttonCount - 1][buttonIdx].x + 76, 242 });
			icon->Init();

			AddChild(::move(icon));

			unique_ptr<UI> name = make_unique<UI>();
			name->SetSprite(_skillName[id]);
			const Vec2Int size = _skillName[id]->GetSize();
			name->SetPos({ _buttonPos[_buttonCount - 1][buttonIdx].x + 100 - size.x / 2, 198 });
			name->Init();

			AddChild(::move(name));

			buttonIdx++;
		}
	}
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
	for (auto& child : _children)
		RemoveChild(child.get());
}

