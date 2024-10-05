#include "pch.h"
#include "Suriken.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "FlipbookActor.h"
#include "Sprite.h"
#include "SpriteActor.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "Projectile.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameScene.h"
#include "Player.h"
#include "Monster.h"
#include "DamageText.h"

Suriken::Suriken()
{
	_flipbook = ResourceManager::GetInstance()->GetFlipbook(L"FB_Suriken");
}

Suriken::~Suriken()
{
}

void Suriken::Init()
{
	SetCooltime(12.f);
	SetDamage();
	SetSkillID(SkillID::ID_Suriken);
}


void Suriken::Use(float deltaTime)
{
	_sumTime += deltaTime;
	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());

	if (_sumTime >= _coolTime)
	{
		Vec2 playerPos = GetOwner()->GetPos();
		for (int32 i = 0; i < _skillLevel; i++)
		{

			unique_ptr<FlipbookActor> suriken = make_unique<FlipbookActor>();
			suriken->SetFlipbook(_flipbook);
			suriken->SetLayer(LAYER_SKILL);

			float initialTheta = i * (360.0f / _skillLevel);
			Vec2 pos;
			pos.x = playerPos.x + _radius * cos(initialTheta * PI / 180.0f);
			pos.y = playerPos.y + _radius * sin(initialTheta * PI / 180.0f);

			suriken->SetPos(pos);

			unique_ptr<SphereCollider> collider = make_unique<SphereCollider>();
			collider->SetCollisionLayer(CLT_PLAYER_SKILL);
			collider->ResetCollisionFlag();
			collider->SetCollisionFlag(CLT_MONSTER);
			collider->SetOwner(suriken.get());
			collider->SetRadius(20);
			//collider->SetShowDebug(true);
			CollisionManager::GetInstance()->AddCollider(collider.get());
			suriken->AddComponent(::move(collider));
			

			suriken->SetSkill2MonsterCallback([this, scene](Collider* other) {
				Monster* monster = dynamic_cast<Monster*>(other->GetOwner());
				if (monster)
				{
					if (monster->TakeDamage(GetDamage()))
						monster->SetState(MonsterState::Death);
					else
					{
						monster->SetState(MonsterState::Hurt);
						const float damagevalue = static_cast<int32>(GetDamage());

						//unique_ptr<DamageText> damagetext = make_unique<DamageText>();
						//damagetext->SetPos(monster->GetPos() + Vec2(10, 0));
						//damagetext->SetText(damagevalue);
						//damagetext->SetLayer(LAYER_DAMAGETEXT);

						//scene->AddActor(::move(damagetext));
					}
				}
			});
			_skillObjectsAndThetas.emplace_back(suriken.get(), initialTheta);
			scene->AddActor(::move(suriken));
		}
		_sumTime = 0.f;
		return;
	}

	if (_sumTime >= _skillDuration)
	{
		for (auto& it : _skillObjectsAndThetas)
		{
			vector<unique_ptr<Component>>& colliders = it.first->GetColliders();
			for (auto& collider : colliders)
			{
				CollisionManager::GetInstance()->RemoveCollider(dynamic_cast<Collider*>(collider.get()));
			}
			scene->RemoveActor(it.first);
		}

		_skillObjectsAndThetas.clear();
		return;
	}

	CalculatePos(deltaTime);
}

void Suriken::SetDamage()
{
	Player* player = dynamic_cast<Player*>(GetOwner());
	float atk = player->GetAttackPower();

	_damage = atk * _atkCoef;
}

void Suriken::CalculatePos(float deltaTime)
{
	Vec2 playerPos = GetOwner()->GetPos();
	float rotationSpeed = 90.0f; // 1초당 회전하는 각도

	for (auto& [suriken, theta] : _skillObjectsAndThetas)
	{
		// 각도를 회전 속도에 따라 증가시킴
		theta += rotationSpeed * deltaTime;

		// 각도를 0~360 사이로 유지
		theta = fmod(theta, 360.0f);

		Vec2 pos;
		pos.x = playerPos.x + _radius * cos(theta * PI / 180.0f);
		pos.y = playerPos.y + _radius * sin(theta * PI / 180.0f);
		suriken->SetPos(pos);
	}
}
