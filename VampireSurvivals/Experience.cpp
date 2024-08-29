#include "pch.h"
#include "Experience.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "Sprite.h"
#include "Collider.h"


Experience::Experience()
{
	SetLayer(LAYER_LOOT);
	Sprite* sprite = ResourceManager::GetInstance()->CreateSprite(L"EXP01", ResourceManager::GetInstance()->GetTexture(L"EXP01"));
	SetSprite(sprite);

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
}

void Experience::Render(HDC hdc)
{
	Super::Render(hdc);
}
