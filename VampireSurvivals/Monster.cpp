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

	//unique_ptr<SphereCollider> collider = make_unique<SphereCollider>();
	//collider->SetOwner(this);
	//collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_MONSTER);
	//collider->ResetCollisionFlag();
	//collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	//collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_PLAYER_SKILL);
	//collider->SetRadius(20);
	////collider->SetShowDebug(true);

	//CollisionManager::GetInstance()->AddCollider(collider.get());
	//AddComponent(::move(collider));
}

Monster::~Monster()
{
}

void Monster::Init()
{
	Super::Init();
	SetLayer(LAYER_MONSTER);
	SetState(MonsterState::Move);
}

void Monster::Update()
{
	Super::Update();

	if (_state == MonsterState::Death)
	{
		UpdateAnimation();
		return;
	}

	float deltaTime = TimeManager::GetInstance()->GetDeltaTime();

	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	Vec2 playerPos = scene->GetPlayerPos();

	_destPos = playerPos;

	Vec2 dir = _destPos - _pos;
	dir.Normalize();
	_pos += dir * _speed;

	if (fabs(dir.x) >= fabs(dir.y))
	{
		if (dir.x > 0)
			SetDir(DIR_RIGHT);
		else
			SetDir(DIR_LEFT);
	}
	else
	{
		if (dir.y > 0)
			SetDir(DIR_DOWN);
		else
			SetDir(DIR_UP);
	}
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
			SetFlipbook(_flipbookIdle[_dir]);
			break;
		case MonsterState::Move:
			SetFlipbook(_flipbookMove[_dir]);
			break;
		case MonsterState::Attack:
			SetFlipbook(_flipbookAttack[_dir]);
			_isAnimationPlaying = true;
			_animationTime = 0.0f;
			break;
		case MonsterState::Hurt:
			SetFlipbook(_flipbookHurt[_dir]);
			_isAnimationPlaying = true;
			_animationTime = 0.0f;
			break;
		case MonsterState::Death:
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

void Monster::OnAnimationFinished()
{
	if (_state == MonsterState::Attack && _onAttackAnimationFinishedCallback)
	{
		_onAttackAnimationFinishedCallback();
	}
	if (_state == MonsterState::Death)
	{
		GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());

		vector<unique_ptr<Component>>& colliders = GetColliders();
		for (auto& collider : colliders)
		{
			CollisionManager::GetInstance()->RemoveCollider(dynamic_cast<Collider*>(collider.get()));
		}

		unique_ptr<Experience> exp = make_unique<Experience>();
		exp->SetPos(_pos);
		exp->SetEXP(30);

		//unique_ptr<SphereCollider> collider = make_unique<SphereCollider>();
		//collider->SetOwner(exp.get());
		//collider->SetCollisionLayer(CLT_EXP);
		//collider->ResetCollisionFlag();
		//collider->AddCollisionFlagLayer(CLT_PLAYER);
		//collider->SetRadius(10);

		//CollisionManager::GetInstance()->AddCollider(collider.get());
		//exp->AddComponent(::move(collider));

		scene->AddActor(::move(exp));

		scene->RemoveActor(this);
		return;
	}


	_isAnimationPlaying = false;
	SetState(MonsterState::Idle);
}

void Monster::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	
}

void Monster::OnComponentEndOverlap(Collider* collider, Collider* other)
{

}

bool Monster::TakeDamage(float damage)
{
	_stat.HP -= damage;

	if (_stat.HP > 0)
		return false;
	return true;
}
