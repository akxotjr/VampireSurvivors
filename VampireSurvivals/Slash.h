#pragma once
#include "Skill.h"

class Sprite;
class Actor;

class Slash : public Skill
{
public:
	Slash();
	virtual ~Slash();

	virtual void Init();
	virtual void Update() {}
	virtual void Render(HDC hdc) {}

	virtual void Use(float deltaTime) override;

	virtual void SetDamage() override;

	int32 GetDegreeSector(Vec2 dir);
	vector<pair<int32, Vec2>> GetAttackSectorsAndDirs(int currentSector, Vec2 currentDir);


protected:
	vector<Actor*> _removeSkillObjects;

	vector<Sprite*> _sprites;
	float _moveSpeed = 5.f;
};

