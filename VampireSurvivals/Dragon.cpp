#include "pch.h"
#include "Dragon.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "Scene.h"
#include "GameScene.h"
#include "SceneManager.h"

Dragon::Dragon()
{
	_flipbookIdle[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonIdleUp");
	_flipbookIdle[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonIdleDown");
	_flipbookIdle[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonIdleLeft");
	_flipbookIdle[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonIdleRight");

	_flipbookAttack[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonAttackUp");
	_flipbookAttack[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonAttackDown");
	_flipbookAttack[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonAttackLeft");
	_flipbookAttack[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonAttackRight");

	_flipbookMove[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonMoveUp");
	_flipbookMove[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonMoveDown");
	_flipbookMove[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonMoveLeft");
	_flipbookMove[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonMoveRight");

	_flipbookHurt[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonHurtUp");
	_flipbookHurt[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonHurtDown");
	_flipbookHurt[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonHurtLeft");
	_flipbookHurt[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonHurtRight");

	_flipbookDeath[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonDeathUp");
	_flipbookDeath[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonDeathDown");
	_flipbookDeath[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonDeathLeft");
	_flipbookDeath[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_DragonDeathRight");

	unique_ptr<SphereCollider> collider = make_unique<SphereCollider>();
	collider->SetOwner(this);
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_MONSTER);
	collider->ResetCollisionFlag();
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_PLAYER_SKILL);
	collider->SetRadius(32);
	//collider->SetShowDebug(true);

	CollisionManager::GetInstance()->AddCollider(collider.get());
	AddComponent(::move(collider));
}

Dragon::~Dragon()
{
}

void Dragon::Init()
{
	Super::Init();
	SetGrade(MonsterGrade::Boss);
	_coolTime = 5.f;
}

void Dragon::Update()
{
	//Super::Update();

	float deltaTime = TimeManager::GetInstance()->GetAdjustDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= _coolTime)
	{

		_sumTime = 0.f;
	}
	
}

void Dragon::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Dragon::Dash()
{
	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	Vec2 playerPos = scene->GetPlayerPos();

	Vec2 dir = playerPos - _pos;
	dir.Normalize();


}

void Dragon::FireBreath()
{

}

void Dragon::ExecutePattern()
{
	_onPattern = true;

	// random pattern
}
