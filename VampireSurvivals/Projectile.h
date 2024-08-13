#pragma once
#include "SpriteActor.h"

class Sprite;
class Collider;
class Actor;

class Projectile : public SpriteActor
{
	using Super = SpriteActor;
public:
	Projectile();
	virtual ~Projectile() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other) override;

	void SetOwner(Actor* owner) { _owner = owner; }
	Actor* GetOwner() { return _owner; }

	void SetDamage();
	float GetDamage() { return _damage; }

protected:
	float	_speed = 5.f;
	float	_damage = 0.f;

	Actor*	_owner = nullptr;
};

