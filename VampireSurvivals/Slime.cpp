#include "pch.h"
#include "Slime.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"

Slime::Slime()
{
	_flipbookIdle[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeIdleUp");
	_flipbookIdle[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeIdleDown");
	_flipbookIdle[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeIdleLeft");
	_flipbookIdle[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeIdleRight");

	_flipbookAttack[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeAttackUp");
	_flipbookAttack[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeAttackDown");
	_flipbookAttack[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeAttackLeft");
	_flipbookAttack[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeAttackRight");

	_flipbookMove[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeMoveUp");
	_flipbookMove[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeMoveDown");
	_flipbookMove[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeMoveLeft");
	_flipbookMove[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeMoveRight");

	_flipbookHurt[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeHurtUp");
	_flipbookHurt[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeHurtDown");
	_flipbookHurt[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeHurtLeft");
	_flipbookHurt[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeHurtRight");

	_flipbookDeath[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeDeathUp");
	_flipbookDeath[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeDeathDown");
	_flipbookDeath[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeDeathLeft");
	_flipbookDeath[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SlimeDeathRight");


	unique_ptr<SphereCollider> collider = make_unique<SphereCollider>();
	collider->SetOwner(this);
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_MONSTER);
	collider->ResetCollisionFlag();
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_PLAYER_SKILL);
	collider->SetRadius(8);
	//collider->SetShowDebug(true);

	CollisionManager::GetInstance()->AddCollider(collider.get());
	AddComponent(::move(collider));
}

Slime::~Slime()
{
}

void Slime::Init()
{
	Super::Init();
}

void Slime::Update()
{
	Super::Update();
}

void Slime::Render(HDC hdc)
{
	Super::Render(hdc);
}
