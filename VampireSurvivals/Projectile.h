#pragma once
#include "SpriteActor.h"

class Sprite;
class Collider;

class Projectile : public SpriteActor
{
	using Super = SpriteActor;
public:
	Projectile();
	virtual ~Projectile() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

protected:
	float _speed = 1.f;
};

