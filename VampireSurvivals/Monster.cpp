#include "pch.h"
#include "Monster.h"
#include "Flipbook.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Scene.h"
#include "DevScene.h"
#include "GameScene.h"
#include "SphereCollider.h"

Monster::Monster()
{
	SetLayer(LAYER_MONSTER);

	_flipbookIdle = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcIdle");
	//_flipbookIdle[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcIdleLeft");

	_flipbookMove[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcMoveRight");
	_flipbookMove[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcMoveLeft");

	_flipbookAttack[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcAttackRight");
	_flipbookAttack[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcAttackLeft");


	SphereCollider* collider = new SphereCollider();
	collider->SetOwner(this);
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_MONSTER);
	collider->ResetCollisionFlag();
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_SKILL);
	collider->SetRadius(10);
	AddComponent(collider);

	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	scene->AddColliders(collider);

}

Monster::~Monster()
{
}

void Monster::Init()
{
	Super::Init();
	SetState(MonsterState::Move);
}

void Monster::Update()
{
	Super::Update();

	float deltaTime = TimeManager::GetInstance()->GetDeltaTime();

	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	Vec2 playerPos = scene->GetPlayerPos();

	_destPos = playerPos;

	Vec2 dir = _destPos - _pos;
	dir.Normalize();

	_pos += dir * 0.1f;

	if (playerPos.x >= _pos.x) _sight = Right;
	else _sight = Left;

	UpdateAnimation();
}

void Monster::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Monster::UpdateAnimation()
{
	switch (_state)
	{
	case MonsterState::Idle:
		SetFlipbook(_flipbookIdle);
		break;
	case MonsterState::Move:
		SetFlipbook(_flipbookMove[_sight]);
		break;
	case MonsterState::Attack:
		SetFlipbook(_flipbookAttack[_sight]);
		break;
	}
}
