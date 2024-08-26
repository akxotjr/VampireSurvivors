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
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"ForceField01"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"ForceField02"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"ForceField03"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"ForceField04"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"ForceField05"));
}

ForceField::~ForceField()
{
}

void ForceField::Init()
{
	SetCooltime(3.f);
	SetDamage();
	SetSkillID(4);
}

void ForceField::Update()
{
	
}

void ForceField::Use(float deltaTime)
{
	if (_createdForceField == false)
	{
		GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());

		SpriteActor* forcefield = new SpriteActor();
		forcefield->SetSprite(_sprites[0]);
		forcefield->SetPos(GetOwner()->GetPos());
		forcefield->SetLayer(LAYER_UNDERSKILL);

		SphereCollider* collider = new SphereCollider();
		collider->SetCollisionLayer(CLT_SKILL);
		collider->ResetCollisionFlag();
		collider->SetCollisionFlag(CLT_MONSTER);
		collider->SetOwner(forcefield);
		collider->SetRadius(_radius);
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

	_skillObjects.front()->SetPos(GetOwner()->GetPos());
}

void ForceField::SetDamage()
{
	Player* player = dynamic_cast<Player*>(GetOwner());
	float atk = player->GetAttackPower();

	_damage = atk * _atkCoef;
}

void ForceField::SkillLevelUP()
{
	Super::SkillLevelUP();
	_radius += 10;

	SpriteActor* forcefield = dynamic_cast<SpriteActor*>(_skillObjects.front());
	forcefield->SetSprite(_sprites[_skillLevel - 1]);
}

