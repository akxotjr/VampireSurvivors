#pragma once
#include "Monster.h"
#include "Skill.h"

class Cyclops : public Monster
{
	using Super = Monster;
public:
	Cyclops();
	virtual ~Cyclops() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other) override;

	float GetAttackRange() { return _attackRange; }

private:
	float	_originSpeed = 0.f;
	bool	_isPlayerInRange = false;
	float	_attackRange = 100.f;

	unique_ptr<Skill>  _skill = nullptr;
};

