#include "pch.h"
#include "Iceburst.h"
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

Iceburst::Iceburst()
{
	_flipbook = ResourceManager::GetInstance()->GetFlipbook(L"FB_Iceburst");

}

Iceburst::~Iceburst()
{
}

void Iceburst::Init()
{
	SetCooltime(3.f);
	SetDamage();
	SetSkillID(SkillID::ID_Iceburst);
}

void Iceburst::Use(float deltaTime)
{
	_sumTime += deltaTime;
	if (_sumTime >= _coolTime)
	{
		GameScene* scene = static_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
		const vector<unique_ptr<Actor>>& monsters = scene->GetMonsters();

		Vec2 pos = {};
		if (monsters.empty())
		{
			return;
		}
		else
		{
			Vec2 playerPos = GetOwner()->GetPos();
			float minDist = 99999.f;
			for (auto& monster : monsters)
			{
				Vec2 monsterPos = monster.get()->GetPos();

				Vec2 dist = playerPos - monsterPos;
				if (minDist > dist.Length())
				{
					minDist = dist.Length();
					pos = monsterPos;
				}
			}

			pos += Vec2(0, -16);
		}

		unique_ptr<FlipbookActor> iceburst = make_unique<FlipbookActor>();
		iceburst->SetFlipbook(_flipbook);
		iceburst->SetPos(pos);
		iceburst->SetLayer(LAYER_SKILL);

		unique_ptr<SphereCollider> collider = make_unique<SphereCollider>();
		collider->SetCollisionLayer(CLT_PLAYER_SKILL);
		collider->ResetCollisionFlag();
		collider->SetCollisionFlag(CLT_MONSTER);
		collider->SetOwner(iceburst.get());
		collider->SetRadius(20);
		//collider->SetShowDebug(true);


		CollisionManager::GetInstance()->AddCollider(collider.get());
		iceburst->AddComponent(::move(collider));
		AddSkillObject(iceburst.get());

		iceburst->SetSkill2MonsterCallback([this, scene](Collider* other) {
			Monster* monster = static_cast<Monster*>(other->GetOwner());
			if (monster)
			{
				if (monster->TakeDamage(GetDamage()))
					monster->SetState(MonsterState::Death);
				else
				{
					monster->SetState(MonsterState::Hurt);
					const float damagevalue = static_cast<int32>(GetDamage());

					unique_ptr<DamageText> damagetext = make_unique<DamageText>();
					damagetext->SetPos(monster->GetPos() + Vec2(10, 0));
					damagetext->SetText(damagevalue);
					damagetext->SetLayer(LAYER_DAMAGETEXT);

					scene->AddActor(::move(damagetext));
				}
			}
		});

		scene->AddActor(::move(iceburst));
		_sumTime = 0.f;
	}
}

void Iceburst::SetDamage()
{
	Player* player = static_cast<Player*>(GetOwner());
	float atk = player->GetAttackPower();

	_damage = atk * _atkCoef;
}

void Iceburst::OnAnimationFinished()
{
	_isAnimationPlaying = false;

}
