#include "pch.h"
#include "Status.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "UI.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameScene.h"
#include "Player.h"

Status::Status()
{
	{
		Sprite* sprite = ResourceManager::GetInstance()->GetSprite(L"InGameStatus");
		SetSprite(sprite);
		SetPos({ 275, 646 });
	}

	_hpBar = ResourceManager::GetInstance()->GetSprite(L"HPbar");
	_expBar = ResourceManager::GetInstance()->GetSprite(L"EXPbar");

	unique_ptr<UI> hpBar = make_unique<UI>();
	hpBar->SetPos({ 295, 702 });
	hpBar->SetSprite(_hpBar);
	AddChild(::move(hpBar));

	unique_ptr<UI> expBar = make_unique<UI>();
	expBar->SetPos({ 295, 708 });
	expBar->SetSprite(_expBar);
	AddChild(::move(expBar));


	_skillIcon[SkillID::ID_Slash] = ResourceManager::GetInstance()->GetSprite(L"SlashSkillIcon36");
	_skillIcon[SkillID::ID_Iceburst] = ResourceManager::GetInstance()->GetSprite(L"IceburstSkillIcon36");
	_skillIcon[SkillID::ID_Lightning] = ResourceManager::GetInstance()->GetSprite(L"LightningSkillIcon36");
	_skillIcon[SkillID::ID_Suriken] = ResourceManager::GetInstance()->GetSprite(L"SurikenSkillIcon36");
	_skillIcon[SkillID::ID_ForceField] = ResourceManager::GetInstance()->GetSprite(L"ForceFieldSkillIcon36");

	_levelToken = ResourceManager::GetInstance()->GetSprite(L"LevelToken");
}

Status::~Status()
{
}

void Status::Init()
{
	Super::Init();

	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	_player = scene->GetPlayer();

	float hpRate = _player->GetHPRate();
	float expRate = _player->GetEXPRate();

	_hpSize = _children[HP]->GetSize();
	_expSize = _children[EXP]->GetSize();
}

void Status::Update()
{
	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	_player = scene->GetPlayer();

	float hpRate = _player->GetHPRate();
	float expRate = _player->GetEXPRate();

	_children[HP]->SetSize({ static_cast<int32>(_hpSize.x * hpRate), _hpSize.y });
	_children[EXP]->SetSize({ static_cast<int32>(_expSize.x * expRate), _expSize.y });

	vector<pair<SkillID, int32>>& skillIDnLevel = _player->GetSkillIDnSkillLevel();

	int32 iconIndex = 0;
	for (auto& skill : skillIDnLevel)
	{
		SkillID id = skill.first;
		int32 level = skill.second;

		auto it = find_if(_skillIDnLevel.begin(), _skillIDnLevel.end(),
			[id](const pair<SkillID, int32>& element) {return element.first == id; });

		if (it != _skillIDnLevel.end())
		{
			if (it->second != level) 
			{
				unique_ptr<UI> levelToken = make_unique<UI>();
				levelToken->SetPos({ 293.f + iconIndex * 46.f + level * 7, 685.f });
				levelToken->SetSprite(_levelToken);
				levelToken->Init();

				AddChild(::move(levelToken));

				it->second = level;
			}
		}
		else
		{
			unique_ptr<UI> icon = make_unique<UI>();
			icon->SetPos({ 293.f + iconIndex * 48.f, 654.f });
			icon->SetSprite(_skillIcon[id]);
			icon->Init();

			AddChild(::move(icon));

			unique_ptr<UI> levelToken = make_unique<UI>();
			levelToken->SetPos({ 290.f + iconIndex * 46.f + level * 7, 685.f });
			levelToken->SetSprite(_levelToken);
			levelToken->Init();

			AddChild(::move(levelToken));

			_skillIDnLevel.push_back(make_pair(id, level));
		}
		iconIndex++;
	}
}

void Status::Render(HDC hdc)
{
	Super::Render(hdc);
}
