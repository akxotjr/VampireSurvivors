#pragma once
#include "Skill.h"

class Flipbook;

class Lightning : public Skill
{
public:
	Lightning();
	virtual ~Lightning();

	virtual void Init();
	virtual void Update() {}
	virtual void Render(HDC hdc) {}

	virtual void Use(float deltaTime) override;

	virtual void SetDamage() override;

protected:
	Flipbook* _flipbook = nullptr;
};

