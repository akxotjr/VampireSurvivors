#include "pch.h"
#include "ForceField.h"
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

ForceField::ForceField()
{
	_sprite = ResourceManager::GetInstance()->GetSprite(L"ForceField");
}

ForceField::~ForceField()
{
}

void ForceField::Init()
{
	SetCooltime(3.f);
	SetDamage();
}

void ForceField::Update()
{
	_skillObjects.front()->SetPos(GetOwner()->GetPos());
}

void ForceField::Use(float deltaTime)
{
	if (_createdForceField == false)
	{
		GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());

		SpriteActor* forcefield = new SpriteActor();
		forcefield->SetSprite(_sprite);
		forcefield->SetPos(GetOwner()->GetPos());
		forcefield->SetLayer(LAYER_UNDERSKILL);

		SphereCollider* collider = new SphereCollider();
		collider->SetCollisionLayer(CLT_SKILL);
		collider->ResetCollisionFlag();
		collider->SetCollisionFlag(CLT_MONSTER);
		collider->SetOwner(forcefield);
		collider->SetRadius(20);
		//collider->SetShowDebug(true);

		forcefield->AddComponent(collider);
		CollisionManager::GetInstance()->AddCollider(collider);

		forcefield->SetSkill2MonsterCallback([this, collider, scene](Collider* other) {
			Monster* monster = dynamic_cast<Monster*>(other->GetOwner());
			if (monster)
			{
				if (monster->TakeDamage(GetDamage()))
					monster->SetState(MonsterState::Death);
				else
				{
					monster->SetState(MonsterState::Hurt);

					const float damagevalue = static_cast<int32>(GetDamage());

					DamageText* damagetext = new DamageText();
					damagetext->SetPos(monster->GetPos() + Vec2(10, 0));
					damagetext->SetText(damagevalue);
					damagetext->SetLayer(LAYER_DAMAGETEXT);

					scene->AddActor(damagetext);
				}
			}
		});

		scene->AddActor(forcefield);

		Skill::AddSkillObject(forcefield);

		_createdForceField = true;
	}
	else
		return;
}

void ForceField::SetDamage()
{
	Player* player = dynamic_cast<Player*>(GetOwner());
	float atk = player->GetAttackPower();

	_damage = atk * _atkCoef;
}
