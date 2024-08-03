#pragma once
#include "SpriteActor.h"

class Sprite;

class Projectile : public SpriteActor
{
	using Super = SpriteActor;
public:
	Projectile();
	virtual ~Projectile() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetAttackDir(Vec2 dir) 
	{ 
		_attackDir = dir;
		_attackDir.Normalize();
	};
	Vec2 GetAttackDir() { return _attackDir; }

protected:

	Vec2 _attackDir = {}; // normal vector
};

