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
}

void Iceburst::Use(float deltaTime)
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

		FlipbookActor* iceburst = new FlipbookActor();
		iceburst->SetFlipbook(_flipbook);
		iceburst->SetPos(pos);
		iceburst->SetLayer(LAYER_SKILL);
		iceburst->SetAnimationFinishedCallback([iceburst, scene]() {
			GameScene* gamescene = dynamic_cast<GameScene*>(scene);
			gamescene->RemoveActor(iceburst);
			//delete(iceburst);
		});

		GameScene* gamescene = dynamic_cast<GameScene*>(scene);
		gamescene->AddActor(iceburst);

		_sumTime = 0.f;
	}
}

void Iceburst::SetDamage()
{
	Player* player = dynamic_cast<Player*>(GetOwner());
	float atk = player->GetAttackPower();

	_damage = atk * _atkCoef;
}

void Iceburst::OnAnimationFinished()
{
	_isAnimationPlaying = false;

}
