#include "pch.h"
#include "StoneSling.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "SpriteActor.h"
#include "Scene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "Cyclops.h"
#include "Player.h"

StoneSling::StoneSling()
{
	_sprite = ResourceManager::GetInstance()->GetSprite(L"M_StoneSling");
}

StoneSling::~StoneSling()
{
}

void StoneSling::Init()
{
	SetDamage();
}

void StoneSling::Update()
{
	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());

	auto it = _skillObjects.begin();
	while (it != _skillObjects.end())
	{
		Vec2 pos = (*it)->GetPos();
		Vec2 startPos = (*it)->GetStartPos();
		Vec2 dist = pos - startPos;
		Cyclops* cyclops = dynamic_cast<Cyclops*>(GetOwner());
		if (dist.Length() >= cyclops->GetAttackRange())
		{
			vector<unique_ptr<Component>>& colliders = (*it)->GetColliders();
			for (auto& collider : colliders)
			{
				CollisionManager::GetInstance()->RemoveCollider(dynamic_cast<Collider*>(collider.get()));
			}
			scene->RemoveActor((*it));
			it = _skillObjects.erase(it);
			continue;
		}
		Vec2 dir = (*it)->GetDir();
		// TODO dir * speed (append speed)
		(*it)->SetPos(pos + dir);
		++it;
	}
}

void StoneSling::Use(float deltaTime)
{
	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	Vec2 playerPos = scene->GetPlayerPos();

	_sumTime += deltaTime;
	if (_sumTime > _coolTime)
	{
		unique_ptr<SpriteActor> stone = make_unique<SpriteActor>();
		stone->SetSprite(_sprite);
		stone->SetPos(_owner->GetPos());
		stone->SetStartPos(_owner->GetPos());
		stone->SetDestPos(playerPos);
		stone->SetLayer(LAYER_SKILL);

		unique_ptr<SphereCollider> collider = make_unique<SphereCollider>();
		collider->SetCollisionLayer(CLT_MONSTER_SKILL);
		collider->ResetCollisionFlag();
		collider->AddCollisionFlagLayer(CLT_PLAYER);
		collider->SetOwner(stone.get());
		collider->SetRadius(6);
		//collider->SetShowDebug(true);

		stone->SetSkill2PlayerCallback([this, scene](Collider* other) {
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			if (other->GetCollisionLayer() == CLT_PLAYER && player)
			{
				if (player->TakeDamage(10))
					player->SetState(PlayerState::Death);
				else
					player->SetState(PlayerState::Hurt);
			}
		});
		CollisionManager::GetInstance()->AddCollider(collider.get());
		stone->AddComponent(::move(collider));


		AddSkillObject(stone.get());
		scene->AddActor(::move(stone));

		_sumTime = 0.f;
	}
}

void StoneSling::SetDamage()
{
}
