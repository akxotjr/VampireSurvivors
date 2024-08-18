#pragma once
#include "Skill.h"

class Flipbook;

class GravityCannon : public Skill
{
public:
	GravityCannon();
	virtual ~GravityCannon();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc) {}

	virtual void Use(float deltaTime) override;

	virtual void SetDamage() override;

	Vec2 GetRandomDestPos();

protected:
	Flipbook*	_flipbook = nullptr;
	float		_dist = 200.f;
	float		_skillDuration = 3.f;
};

