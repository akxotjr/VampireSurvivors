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
		SpriteActor* forcefield = new SpriteActor();
		forcefield->SetSprite(_sprite);
		forcefield->SetPos(GetOwner()->GetPos());
		forcefield->SetLayer(LAYER_UNDERSKILL);

		GameScene* gamescene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
		gamescene->AddActor(forcefield);

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
