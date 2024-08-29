#pragma once
#include "Skill.h"

class Sprite;

class StoneSling : public Skill
{
public:
	StoneSling();
	virtual ~StoneSling();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc) {}

	virtual void Use(float deltaTime);
	virtual void SetDamage();

private:
	Sprite* _sprite = nullptr;
};

