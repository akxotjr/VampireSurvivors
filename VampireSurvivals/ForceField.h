#pragma once
#include "Skill.h"

class Flipbook;
class Sprite;

class ForceField : public Skill
{
	using Super = Skill;
public:
	ForceField();
	virtual ~ForceField();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc) {}

	virtual void Use(float deltaTime) override;

	virtual void SetDamage() override;

	virtual void SkillLevelUP();

private:
	vector<Sprite*> _sprites;

protected:
	float			_radius = 32;
	bool			_createdForceField = false;
};

