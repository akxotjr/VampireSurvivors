#include "pch.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

Collider::Collider(ColliderType colliderType)
{
}

Collider::~Collider()
{
}

void Collider::Init()
{
}

void Collider::Update()
{
}

void Collider::Render(HDC hdc)
{
}

bool Collider::CheckCollision(Collider* other)
{
	uint8 layer = other->GetCollisionLayer();
	if (_collisionFlag & (1 << layer))
		return true;

	return false;
}
