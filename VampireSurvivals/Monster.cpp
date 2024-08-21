#include "pch.h"
#include "Monster.h"
#include "Flipbook.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "CollisionManager.h"
#include "Scene.h"
#include "DevScene.h"
#include "GameScene.h"
#include "SphereCollider.h"
#include "Projectile.h"
#include "Experience.h"

Monster::Monster()
{
	_stat = { 100, 100, 10 };

	SetLayer(LAYER_MONSTER);

	_flipbookIdle[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcIdleRight");
	_flipbookIdle[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcIdleLeft");

	_flipbookMove[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcMoveRight");
	_flipbookMove[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcMoveLeft");

	_flipbookAttack[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcAttackRight");
	_flipbookAttack[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcAttackLeft");

	_flipbookHurt[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcHurtRight");
	_flipbookHurt[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcHurtLeft");

	_flipbookDeath[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcDeathRight");
	_flipbookDeath[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcDeathLeft");


	SphereCollider* collider = new SphereCollider();
	collider->SetOwner(this);
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_MONSTER);
	collider->ResetCollisionFlag();
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_SKILL);
	collider->SetRadius(20);
	AddComponent(collider);

	CollisionManager::GetInstance()->AddCollider(collider);

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

void Monster::SetState(MonsterState state)
{
	if (!_isAnimationPlaying)
	{
		_state = state;
		UpdateAnimation();
	}
}

void Monster::UpdateAnimation()
{
	if (!_isAnimationPlaying)
	{
		switch (_state)
		{
		case MonsterState::Idle:
			SetFlipbook(_flipbookIdle[_sight]);
			break;
		case MonsterState::Move:
			SetFlipbook(_flipbookMove[_sight]);
			break;
		case MonsterState::Attack:
			SetFlipbook(_flipbookAttack[_sight]);
			_isAnimationPlaying = true;
			_animationTime = 0.0f;
			break;
		case MonsterState::Hurt:
			SetFlipbook(_flipbookHurt[_sight]);
			_isAnimationPlaying = true;
			_animationTime = 0.0f;
			break;
		case MonsterState::Death:
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
			if (_state == MonsterState::Death)
			{
				GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
				scene->RemoveActor(this);

				Experience* exp = new Experience();
				exp->SetPos(_pos);
				exp->SetEXP(30);

				scene->AddActor(exp);
				return;
			}
			OnAnimationFinished();
		}
	}

}

void Monster::OnAnimationFinished()
{
	_isAnimationPlaying = false;
	SetState(MonsterState::Move);
}

void Monster::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	
}

void Monster::OnComponentEndOverlap(Collider* collider, Collider* other)
{

	//if (other->GetCollisionLayer() == CLT_MONSTER)
	//{
	//	Monster* monster = dynamic_cast<Monster*>(other->GetOwner());
	//	if (!TakeDamage(monster->GetDamage()))
	//		SetState(MonsterState::Hurt);
	//	else
	//		SetState(MonsterState::Death);
	//}
	if (_state == MonsterState::Death)
	{
		CollisionManager::GetInstance()->RemoveCollider(collider);

		//delete(this);
	}
}

bool Monster::TakeDamage(float damage)
{
	_stat.HP -= damage;

	if (_stat.HP > 0)
		return false;
	return true;
}
