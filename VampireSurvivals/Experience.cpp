#include "pch.h"
#include "Experience.h"
#include "ResourceManager.h"
#include "Component.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "Sprite.h"
#include "Collider.h"
#include "Player.h"
#include "Scene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "EventManager.h"

Experience::Experience()
{
	SetLayer(LAYER_LOOT);
	_sprite = ResourceManager::GetInstance()->GetSprite(L"EXP01");

	unique_ptr<SphereCollider> collider = make_unique<SphereCollider>();
	collider->SetOwner(this);
	collider->SetCollisionLayer(CLT_EXP);
	collider->ResetCollisionFlag();
	collider->AddCollisionFlagLayer(CLT_PLAYER);
	collider->SetRadius(10);

	CollisionManager::GetInstance()->AddCollider(collider.get());
	AddComponent(::move(collider));
}

Experience::~Experience()
{
}

void Experience::Init()
{
	Super::Init();
}

void Experience::Update()
{
	Super::Update();
	//if (_takenEXP)
	//{
	//	GameScene* scene = static_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	//	vector<unique_ptr<Component>>& colliders = GetColliders();
	//	for (auto& collider : colliders)
	//	{
	//		CollisionManager::GetInstance()->RemoveCollider(static_cast<Collider*>(collider.get()));
	//	}

	//	//scene->RemoveActor(this);
	//	EventManager::GetInstance()->AddEvent([scene, this]() {
	//		scene->RemoveActor(this);
	//		});
	//	return;
	//}
}

void Experience::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Experience::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (other->GetCollisionLayer() == CLT_PLAYER)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player == nullptr) return;

		player->TakeEXP(GetEXP());

		//CollisionManager::GetInstance()->RemoveCollider(collider);
		GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
		EventManager::GetInstance()->AddEvent([scene, this, collider]() {
			CollisionManager::GetInstance()->RemoveCollider(collider);
			scene->RemoveActor(this);
			});
	}
}

void Experience::OnComponentEndOverlap(Collider* collider, Collider* other)
{

}
