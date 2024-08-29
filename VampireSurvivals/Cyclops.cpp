#include "pch.h"
#include "Cyclops.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "TimeManager.h"
#include "StoneSling.h"
#include "Skill.h"

Cyclops::Cyclops()
{
	_flipbookIdle[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsIdleUp");
	_flipbookIdle[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsIdleDown");
	_flipbookIdle[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsIdleLeft");
	_flipbookIdle[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsIdleRight");

	_flipbookAttack[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsAttackUp");
	_flipbookAttack[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsAttackDown");
	_flipbookAttack[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsAttackLeft");
	_flipbookAttack[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsAttackRight");

	_flipbookMove[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsMoveUp");
	_flipbookMove[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsMoveDown");
	_flipbookMove[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsMoveLeft");
	_flipbookMove[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsMoveRight");

	_flipbookHurt[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsHurtUp");
	_flipbookHurt[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsHurtDown");
	_flipbookHurt[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsHurtLeft");
	_flipbookHurt[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsHurtRight");

	_flipbookDeath[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsDeathUp");
	_flipbookDeath[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsDeathDown");
	_flipbookDeath[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsDeathLeft");
	_flipbookDeath[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_CyclopsDeathRight");

	{
		unique_ptr<SphereCollider> collider = make_unique<SphereCollider>();
		collider->SetOwner(this);
		collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_MONSTER);
		collider->ResetCollisionFlag();
		collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
		collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_PLAYER_SKILL);
		collider->SetRadius(16);
		collider->SetShowDebug(true);
		
		CollisionManager::GetInstance()->AddCollider(collider.get());
		AddComponent(::move(collider));
	}
	{
		unique_ptr<SphereCollider> collider = make_unique<SphereCollider>();
		collider->SetOwner(this);
		collider->SetCollisionLayer(CLT_MONSTER_ATK_RANGE);
		collider->ResetCollisionFlag();
		collider->AddCollisionFlagLayer(CLT_PLAYER);
		collider->SetRadius(_attackRange);
		collider->SetShowDebug(true);

		CollisionManager::GetInstance()->AddCollider(collider.get());
		AddComponent(::move(collider));
	}

	_skill = make_unique<StoneSling>();
	_skill->SetOwner(this);
	_skill->Init();
}

Cyclops::~Cyclops()
{
}

void Cyclops::Init()
{
	Super::Init();
	SetGrade(MonsterGrade::Rare);

}

void Cyclops::Update()
{
	Super::Update();

	if (_isPlayerInRange)
	{
		float deltaTime = TimeManager::GetInstance()->GetDeltaTime();
		_sumTime += deltaTime;
		_skill->Use(deltaTime);
		if (_sumTime >= _coolTime)
		{
			SetState(MonsterState::Attack);
			_sumTime = 0.f;
		}
	}

	_skill->Update();
	
}

void Cyclops::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Cyclops::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (collider->GetCollisionLayer() == CLT_MONSTER_ATK_RANGE && other->GetCollisionLayer() == CLT_PLAYER)
	{
		_originSpeed = _speed;
		_speed = 0.f;
		_isPlayerInRange = true;
		SetState(MonsterState::Idle);
	}
}

void Cyclops::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	if (collider->GetCollisionLayer() == CLT_MONSTER_ATK_RANGE && other->GetCollisionLayer() == CLT_PLAYER)
	{
		_speed = _originSpeed;
		_isPlayerInRange = false;
		SetState(MonsterState::Move);
	}
}
