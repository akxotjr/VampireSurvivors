#include "pch.h"
#include "Lightning.h"
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

Lightning::Lightning()
{
	_flipbook = ResourceManager::GetInstance()->GetFlipbook(L"FB_Lightning");
}

Lightning::~Lightning()
{
}

void Lightning::Init()
{
	SetCooltime(3.f);
	SetDamage();
	SetSkillID(SkillID::ID_Lightning);
}

void Lightning::Use(float deltaTime)
{
	_sumTime += deltaTime;
	if (_sumTime >= _coolTime)
	{
		GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
		const vector<unique_ptr<Actor>>& monsters = scene->GetMonsters();

		Vec2 pos = {};
		if (monsters.empty())
		{
			return;
		}
		else
		{
			float maxHP = 0.f;
			for (auto& monster : monsters)
			{
				Vec2 monsterPos = monster.get()->GetPos();
				float curHP = dynamic_cast<Monster*>(monster.get())->GetInfo().stat.HP;
				if (maxHP > curHP)
				{
					maxHP = curHP;
					pos = monsterPos;
				}
			}
		}

		unique_ptr<FlipbookActor> lightning = make_unique<FlipbookActor>();
		lightning->SetFlipbook(_flipbook);
		lightning->SetPos(pos);
		lightning->SetLayer(LAYER_SKILL);

		unique_ptr<SphereCollider> collider = make_unique<SphereCollider>();
		collider->SetCollisionLayer(CLT_PLAYER_SKILL);
		collider->ResetCollisionFlag();
		collider->SetCollisionFlag(CLT_MONSTER);
		collider->SetOwner(lightning.get());
		collider->SetRadius(20);
		CollisionManager::GetInstance()->AddCollider(collider.get());
		lightning->AddComponent(::move(collider));


		lightning->SetSkill2MonsterCallback([this, scene](Collider* other) {
			Monster* monster = dynamic_cast<Monster*>(other->GetOwner());
			if (monster)
			{
				if (monster->TakeDamage(GetDamage()))
					monster->SetState(MonsterState::Death);
				else
				{
					monster->SetState(MonsterState::Hurt);

					//const float damagevalue = static_cast<int32>(GetDamage());

					//unique_ptr<DamageText> damagetext = make_unique<DamageText>();
					//damagetext->SetPos(monster->GetPos() + Vec2(10, 0));
					//damagetext->SetText(damagevalue);
					//damagetext->SetLayer(LAYER_DAMAGETEXT);

					//scene->AddActor(::move(damagetext));
				}
			}
		});

		scene->AddActor(::move(lightning));
		_sumTime = 0.f;

	}
}

void Lightning::SetDamage()
{
	Player* player = dynamic_cast<Player*>(GetOwner());
	float atk = player->GetAttackPower();

	_damage = atk * _atkCoef;
}
