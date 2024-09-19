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
	SetSkillID(SkillID::ID_ForceField);
}

void ForceField::Update()
{
	
}

void ForceField::Use(float deltaTime)
{
	if (_createdForceField == false)
	{
		GameScene* scene = static_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());

		unique_ptr<SpriteActor> forcefield = make_unique<SpriteActor>();
		forcefield->SetSprite(_sprites[0]);
		forcefield->SetPos(GetOwner()->GetPos());
		forcefield->SetLayer(LAYER_UNDERSKILL);

		unique_ptr<SphereCollider> collider = make_unique<SphereCollider>();
		collider->SetCollisionLayer(CLT_PLAYER_SKILL);
		collider->ResetCollisionFlag();
		collider->SetCollisionFlag(CLT_MONSTER);
		collider->SetOwner(forcefield.get());
		collider->SetRadius(_radius);
		//collider->SetShowDebug(true);

		CollisionManager::GetInstance()->AddCollider(collider.get());
		forcefield->AddComponent(::move(collider));
		

		forcefield->SetSkill2MonsterCallback([this, scene](Collider* other) {
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
		Skill::AddSkillObject(forcefield.get());
		scene->AddActor(::move(forcefield));

		_createdForceField = true;
	}

	_skillObjects.front()->SetPos(GetOwner()->GetPos());
}

void ForceField::SetDamage()
{
	Player* player = static_cast<Player*>(GetOwner());
	float atk = player->GetAttackPower();

	_damage = atk * _atkCoef;
}

void ForceField::SkillLevelUP()
{
	Super::SkillLevelUP();
	_radius += 10;

	SpriteActor* forcefield = static_cast<SpriteActor*>(_skillObjects.front());
	forcefield->SetSprite(_sprites[_skillLevel - 1]);
}

