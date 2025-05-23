#include "pch.h"
#include "Projectile.h"
#include "SpriteActor.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "SphereCollider.h"
#include "GameScene.h"
#include "Player.h"
#include "Actor.h"

Projectile::Projectile()
{
	//SphereCollider* collider = new SphereCollider();
	//collider->SetOwner(this);
	//collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_SKILL);
	//collider->ResetCollisionFlag();
	//collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_MONSTER);
	//collider->SetRadius(10);
	//AddComponent(collider);

	//CollisionManager::GetInstance()->AddCollider(collider);
}

Projectile::~Projectile()
{
}

void Projectile::Init()
{
	Super::Init();
}

void Projectile::Update()
{
	Super::Update();

	Vec2 nextPos = _pos + _dir * _speed;
	Vec2 cameraPos = SceneManager::GetInstance()->GetCameraPos();
	//if ((cameraPos.x - GWinSizeX / 2) >= nextPos.x || (cameraPos.x + GWinSizeX / 2) <= nextPos.x || (cameraPos.y - GWinSizeY) >= nextPos.y || (cameraPos.y + GWinSizeY) <= nextPos.y)
	//{
	//	SceneManager::GetInstance()->GetCurrentScene()->RemoveActor(this);
	//}
	//else
	//{
		_pos = nextPos;
	//}
}

void Projectile::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Projectile::OnComponentBeginOverlap(Collider* collider, Collider* other)
{

}

void Projectile::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	//GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	//scene->RemoveActor(this);

	//CollisionManager::GetInstance()->RemoveCollider(collider);
}
