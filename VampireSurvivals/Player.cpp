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

Player::Player()
{
	_stat = { 100, 100, 30 };


	SetLayer(LAYER_PLAYER);

	_flipbookIdle[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierIdleRight");
	_flipbookIdle[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierIdleLeft");

	_flipbookMove[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierMoveRight");
	_flipbookMove[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierMoveLeft");

	_flipbookAttack[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierAttackRight");
	_flipbookAttack[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierAttackLeft");

	_flipbookHurt[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierHurtRight");
	_flipbookHurt[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierHurtLeft");

	_flipbookDeath[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierDeathRight");
	_flipbookDeath[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierDeathLeft");


	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);

	SphereCollider* collider = new SphereCollider();
	collider->SetOwner(this);
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->ResetCollisionFlag();
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_MONSTER);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_EXP);
	collider->SetRadius(20);
	AddComponent(collider);

	CollisionManager::GetInstance()->AddCollider(collider);

	Slash* slash = new Slash();
	slash->SetOwner(this);
	AddSkill(slash);

	Iceburst* iceburst = new Iceburst();
	iceburst->SetOwner(this);
	iceburst->Init();
	AddSkill(iceburst);

	//GravityCannon* gravitcannon = new GravityCannon();
	//gravitcannon->SetOwner(this);
	//gravitcannon->Init();
	//AddSkill(gravitcannon);

	ForceField* forcefield = new ForceField();
	forcefield->SetOwner(this);
	forcefield->Init();
	AddSkill(forcefield);

	Lightning* lightning = new Lightning();
	lightning->SetOwner(this);
	lightning->Init();
	AddSkill(lightning);

	Suriken* suriken = new Suriken();
	suriken->SetOwner(this);
	suriken->Init();
	AddSkill(suriken);
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

	{
		UpdateDir();
		if (!_keyPressed)
		{
			SetState(PlayerState::Idle);
		}
		else
		{
			SetState(PlayerState::Move);
			if (_dir & (1 << 1))
			{
				_pos.x += 100 * deltaTime;
				_sight = Sight::Right;
			}
			if (_dir & (1 << 2))
			{
				_pos.x -= 100 * deltaTime;
				_sight = Sight::Left;
			}
			if (_dir & (1 << 3))
			{
				_pos.y -= 100 * deltaTime;
			}
			if (_dir & (1 << 4))
			{
				_pos.y += 100 * deltaTime;
			}
		}
	}
	UpdateAnimation();

	UpdateSkill();
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
	Utils::DrawHP(hdc, Vec2(480, 340), 30, 5, _stat.HP / _stat.MaxHP);
}

void Player::SetState(PlayerState state)
{
	if (!_isAnimationPlaying)
	{
		_state = state;
		UpdateAnimation();
	}
}

void Player::UpdateDir()
{
	uint8 dir = 0;
	if (InputManager::GetInstance()->GetButton(KeyType::D))
	{
		dir |= (1<<1);
	}
	if (InputManager::GetInstance()->GetButton(KeyType::A))
	{
		dir |= (1<<2);
	}
	if (InputManager::GetInstance()->GetButton(KeyType::W))
	{
		dir |= (1<<3);
	}
	if (InputManager::GetInstance()->GetButton(KeyType::S))
	{
		dir |= (1<<4);
	}

	if ((dir & (1<<1) && dir & (1<<2)) || (dir & (1<<3) && (dir & (1<<4))) || dir == 0)
	{
		_keyPressed = false;
		return;
	}
	_keyPressed = true;
	_dir = (Dir)dir;
}

void Player::UpdateAnimation()
{
	if (!_isAnimationPlaying)
	{
		switch (_state)
		{
		case PlayerState::Idle:
			if (_keyPressed)
				SetFlipbook(_flipbookMove[_sight]);
			else
				SetFlipbook(_flipbookIdle[_sight]);
			break;
		case PlayerState::Move:
			SetFlipbook(_flipbookMove[_sight]);
			break;
		case PlayerState::Attack:
			SetFlipbook(_flipbookAttack[_sight]);
			_isAnimationPlaying = true;
			_animationTime = 0.0f;
			break;
		case PlayerState::Hurt:
			SetFlipbook(_flipbookHurt[_sight]);
			_isAnimationPlaying = true;
			_animationTime = 0.0f;
			break;
		case PlayerState::Death:
			SetFlipbook(_flipbookDeath[_sight]);
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
	
	SelectSkillPanel* ssp = new SelectSkillPanel();
	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	scene->AddUI(ssp);
}

void Player::RandomSkill()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	//uniform_random_bit_generator

	//int32 S = 0;
	//for (int32 i = 1; i <= 10; i++)
	//{
	//	if()
	//}
}


