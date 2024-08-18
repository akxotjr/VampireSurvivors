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
}

void Lightning::Use(float deltaTime)
{
	_sumTime += deltaTime;
	if (_sumTime >= _coolTime)
	{
		Scene* scene = SceneManager::GetInstance()->GetCurrentScene();
		const vector<Actor*>& monsters = scene->GetMonsters();

		Vec2 pos;
		if (monsters.empty())
		{
			pos = { 300,300 };
		}
		else
		{
			pos = monsters.front()->GetPos() + Vec2(0, -16);
		}

		FlipbookActor* lightning = new FlipbookActor();
		lightning->SetFlipbook(_flipbook);
		lightning->SetPos(pos);
		lightning->SetLayer(LAYER_SKILL);
		lightning->SetAnimationFinishedCallback([lightning, scene]() {
			GameScene* gamescene = dynamic_cast<GameScene*>(scene);
			gamescene->RemoveActor(lightning);
			//delete(iceburst);
		});

		GameScene* gamescene = dynamic_cast<GameScene*>(scene);
		gamescene->AddActor(lightning);

		_sumTime = 0.f;

	}
}

void Lightning::SetDamage()
{
	Player* player = dynamic_cast<Player*>(GetOwner());
	float atk = player->GetAttackPower();

	_damage = atk * _atkCoef;
}
