#pragma once
#include "Skill.h"

class Flipbook;
class FlipbookActor;

class Suriken : public Skill
{
public:
	Suriken();
	virtual ~Suriken();

	virtual void Init();
	virtual void Update() {};
	virtual void Render(HDC hdc) {}

	virtual void Use(float deltaTime) override;

	virtual void SetDamage() override;

	void CalculatePos(float theta);

protected:
	Flipbook* _flipbook = nullptr;
	float	  _radius = 50.f;
	float	  _skillDuration = 10.f;
	float	  _curSkillDuration = 0.f;

	vector<pair<FlipbookActor*, float>> _skillObjectsAndThetas;
};

