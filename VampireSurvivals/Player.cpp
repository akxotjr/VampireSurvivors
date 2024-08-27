#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Flipbook.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "DevScene.h"
#include "GameScene.h"
#include "CameraComponent.h"
#include "Projectile.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Monster.h"
#include "Slash.h"
#include "Skill.h"
#include "Iceburst.h"
#include "GravityCannon.h"
#include "ForceField.h"
#include "Lightning.h"
#include "Suriken.h"
#include "Experience.h"
#include "SelectSkillPanel.h"
#include "Button.h"
#include "Sprite.h"

Player::Player()
{
	_stat = { 100, 100, 50 };


	SetLayer(LAYER_PLAYER);


	_flipbookIdle[DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerIdleUp");
	_flipbookIdle[DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerIdleDown");
	_flipbookIdle[DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerIdleLeft");
	_flipbookIdle[DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerIdleRight");

	_flipbookAttack[DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerAttackUp");
	_flipbookAttack[DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerAttackDown");
	_flipbookAttack[DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerAttackLeft");
	_flipbookAttack[DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerAttackRight");

	_flipbookMove[DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerMoveUp");
	_flipbookMove[DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerMoveDown");
	_flipbookMove[DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerMoveLeft");
	_flipbookMove[DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerMoveRight");

	_flipbookHurt[DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerHurtUp");
	_flipbookHurt[DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerHurtDown");
	_flipbookHurt[DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerHurtLeft");
	_flipbookHurt[DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerHurtRight");

	_flipbookDeath[DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerDeathUp");
	_flipbookDeath[DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerDeathDown");
	_flipbookDeath[DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerDeathLeft");
	_flipbookDeath[DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerDeathRight");

	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);

	SphereCollider* collider = new SphereCollider();
	collider->SetOwner(this);
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->ResetCollisionFlag();
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_MONSTER);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_MONSTER_ATK_RANGE);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_EXP);
	collider->SetRadius(20);
	collider->SetShowDebug(true);
	AddComponent(collider);

	CollisionManager::GetInstance()->AddCollider(collider);

	Slash* slash = new Slash();
	slash->SetOwner(this);
	slash->Init();
	AddSkill(slash);
}

Player::~Player()
{
}

void Player::Init()
{
	Super::Init();
	SetState(PlayerState::Idle);
}

void Player::Update()
{
	Super::Update();

	float deltaTime = TimeManager::GetInstance()->GetDeltaTime();

	_sumTime += deltaTime;
	UseSkill(deltaTime);

	if (_sumTime > _coolTime)
	{
		if (_sumTime > _coolTime + 0.5f)
		{
			SetState(PlayerState::Attack);
			_sumTime = 0.f;

		}
	}

	Vec2 dir = UpdateDir();
	if (dir == Vec2(0,0))
	{
		SetState(PlayerState::Idle);
	}
	else
	{
		SetState(PlayerState::Move);
		_pos += dir * _speed;
	}
	UpdateAnimation();

	UpdateSkill();
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
	Utils::DrawHP(hdc, Vec2(480, 340), 30, 5, _stat.HP / _stat.MaxHP);

	Vec2 pos = { 10, 50 };
	for (auto& skill : _skills)
	{
		TextOut(hdc, pos.x, pos.y, _skillNames[skill->GetSkillID()].c_str(), _skillNames[skill->GetSkillID()].length());
		pos.y += 15;
	}
}

void Player::SetState(PlayerState state)
{
	if (!_isAnimationPlaying)
	{
		_state = state;
		UpdateAnimation();
	}
}

Vec2 Player::UpdateDir()
{
	Vec2 dir = { 0,0 };

	if (InputManager::GetInstance()->GetButton(KeyType::W))
	{
		dir += {0, -1};
		_dir = Dir::DIR_UP;
	}
	else if (InputManager::GetInstance()->GetButton(KeyType::S))
	{
		dir += {0, 1};
		_dir = Dir::DIR_DOWN;
	}

	if (InputManager::GetInstance()->GetButton(KeyType::D))
	{
		dir += {1, 0};
		_dir = Dir::DIR_RIGHT;
	}
	else if (InputManager::GetInstance()->GetButton(KeyType::A))
	{
		dir += {-1, 0};
		_dir = Dir::DIR_LEFT;
	}

	dir.Normalize();
	return dir;
}

void Player::UpdateAnimation()
{
	if (!_isAnimationPlaying)
	{
		switch (_state)
		{
		case PlayerState::Idle:
			if (_keyPressed)
				SetFlipbook(_flipbookMove[_dir]);
			else
				SetFlipbook(_flipbookIdle[_dir]);
			break;
		case PlayerState::Move:
			SetFlipbook(_flipbookMove[_dir]);
			break;
		case PlayerState::Attack:
			SetFlipbook(_flipbookAttack[_dir]);
			_isAnimationPlaying = true;
			_animationTime = 0.0f;
			break;
		case PlayerState::Hurt:
			SetFlipbook(_flipbookHurt[_dir]);
			_isAnimationPlaying = true;
			_animationTime = 0.0f;
			break;
		case PlayerState::Death:
			SetFlipbook(_flipbookDeath[_dir]);
			_isAnimationPlaying = true;
			_animationTime = 0.0f;
			break;
		}
	}
	else
	{
		_animationTime += TimeManager::GetInstance()->GetDeltaTime();
		if (_animationTime >= GetFlipbookDuration())
		{
			OnAnimationFinished();
		}
	}
}

void Player::OnAnimationFinished()
{
	_isAnimationPlaying = false;
	SetState(PlayerState::Idle);
}


bool Player::TakeDamage(int32 damage)
{
	_stat.HP -= damage;

	if (_stat.HP > 0)
		return false;
	return true;
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (other->GetCollisionLayer() == CLT_MONSTER)
	{
		Monster* monster = dynamic_cast<Monster*>(other->GetOwner());
		if (!TakeDamage(monster->GetDamage()))
			SetState(PlayerState::Hurt);
		else
			SetState(PlayerState::Death);
	}
	else if (other->GetCollisionLayer() == CLT_EXP)
	{
		Experience* exp = dynamic_cast<Experience*>(other->GetOwner());
		TakeEXP(exp->GetEXP());

		GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
		scene->RemoveActor(other->GetOwner());
		CollisionManager::GetInstance()->RemoveCollider(dynamic_cast<Collider*>(exp->GetCollider()));
	}
}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{

}

void Player::UseSkill(float deltaTime)
{
	for (auto& skill : _skills)
		skill->Use(deltaTime);
}

void Player::UpdateSkill()
{
	for (auto& skill : _skills)
		skill->Update();
}

void Player::TakeEXP(int32 exp)
{
	_exp += exp;
	if (_exp >= _maxExp)
	{
		int32 overExp = _exp - _maxExp;
		_exp = overExp;

		_maxExp += 20;

		LevelUP();
	}
}

void Player::LevelUP()
{
	//TODO
	_level++;
	TimeManager::GetInstance()->SetTimeScale(0.f);
	RandomSkill();
}

void Player::RandomSkill()
{
	int32 possibleSkills = (1 << 5) - 1;
	int32 selectedSkills = 0;

	if (_skills.size() == 4)
	{
		possibleSkills = 0;
		for (auto skill : _skills)
		{
			possibleSkills |= (1 << skill->GetSkillID());
		}
	}
	for (auto skill : _skills)
	{
		if (skill->GetSkillLevel() == 5)
		{
			possibleSkills &= ~(1 << skill->GetSkillID());
		}
	}

	::random_device rd;
	::mt19937 gen(rd());

	::uniform_int_distribution<int32> dist(0, 5);

	int32 count = 0; 
	
	while (count < 3)
	{
		int32 i = dist(gen);

		if (possibleSkills & (1 << i))
		{
			selectedSkills |= (1 << i);
			possibleSkills &= ~(1 << i);
			count++;
		}
	}

	int32 buttonCnt = 0;
	vector<Vec2> pos = { {245, 360}, {480, 360}, {715, 360} };

	SelectSkillPanel* ssp = new SelectSkillPanel();
	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());

	for (int32 i = 0; i < 5; i++)
	{
		if (selectedSkills & (1 << i))
		{
			GenerateSkillButton(i, pos[buttonCnt], ssp);
			buttonCnt++;
		}
	}

	scene->AddUI(ssp);
}

void Player::GenerateSkillButton(int32 id, Vec2 pos, SelectSkillPanel* panel)
{
	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	Sprite* sprite = ResourceManager::GetInstance()->GetSprite(L"SelectSkillButton");
	{
		Button* button = new Button();
		button->SetSprite(sprite, BS_Default);
		button->SetSprite(sprite, BS_Clicked);
		button->SetSprite(sprite, BS_Pressed);
		button->SetPos({ pos.x, pos.y });
		button->SetSize(sprite->GetSize());
		button->SetText(_skillNames[id]);
		button->AddOnClickDelegate(this, &Player::SkillLevelUP, id, panel);
		button->Init();

		panel->AddChild(button);

		scene->AddUI(button);
	}
}

void Player::SkillLevelUP(int32 id, SelectSkillPanel* panel)
{
	bool flag = false;
	for (auto& skill : _skills)
	{
		if (skill->GetSkillID() == id)
		{
			skill->SkillLevelUP();
			
			flag = true;
			break;
		}
	}
	if (!flag)
	{
		switch (id)
		{
		case 0:
		{
			Slash* slash = new Slash();
			slash->SetOwner(this);
			slash->Init();
			AddSkill(slash);
		}
			break;
		case 1:
		{
			Iceburst* iceburst = new Iceburst();
			iceburst->SetOwner(this);
			iceburst->Init();
			AddSkill(iceburst);
		}
			break;
		case 2:
		{
			Lightning* lightning = new Lightning();
			lightning->SetOwner(this);
			lightning->Init();
			AddSkill(lightning);
		}
			break;
		case 3:
		{
			Suriken* suriken = new Suriken();
			suriken->SetOwner(this);
			suriken->Init();
			AddSkill(suriken);
		}
			break;
		case 4:
		{
			ForceField* forcefield = new ForceField();
			forcefield->SetOwner(this);
			forcefield->Init();
			AddSkill(forcefield);
		}
			break;
		}
	}

	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	panel->RemoveAllChild();
	scene->RemmoveUI(panel);

	TimeManager::GetInstance()->SetTimeScale(1.f);
}




