#pragma once
#include "Skill.h"

class Flipbook;
class Sprite;

class ForceField : public Skill
{
public:
	ForceField();
	virtual ~ForceField();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc) {}

	virtual void Use(float deltaTime) override;

	virtual void SetDamage() override;

protected:
	Sprite*	 _sprite = nullptr;

	bool	 _createdForceField = false;
};

