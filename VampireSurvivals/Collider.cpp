#include "pch.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

Collider::Collider(ColliderType colliderType) : _colliderType(colliderType)
{
	SetComponentType(COLLIDER);
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

bool Collider::CheckCollisionBox2Box(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();
	RECT intersect = {};

	return ::IntersectRect(&intersect, &r1, &r2);
}

bool Collider::CheckCollisionSphere2Box(SphereCollider* s1, BoxCollider* b2)
{
	return false;
}

bool Collider::CheckCollisionSphere2Sphere(SphereCollider* s1, SphereCollider* s2)
{
	Vec2 p1 = s1->GetOwner()->GetPos();
	float r1 = s1->GetRadius();

	Vec2 p2 = s2->GetOwner()->GetPos();
	float r2 = s2->GetRadius();

	Vec2 dir = p1 - p2;
	float dist = dir.Length();

	return dist <= r1 + r2;
}
