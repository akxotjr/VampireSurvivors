#pragma once
#include "Component.h"

class Skill : public Component
{
public:
	Skill();
	virtual ~Skill();

	virtual void Init() {}
	virtual void Update() {}
	virtual void Render(HDC hdc) {}

	virtual void Use(float deltaTime) abstract;

	int32 GetSkillLevel() { return _skillLevel; }

	void SetCooltime(float cooltime) { _coolTime = cooltime; }
	float GetCooltime() { return _coolTime; }

	virtual void SetDamage() abstract;
	float GetDamage() { return _damage; }

	void SetAtkCoef(float coef) { _atkCoef = coef; }
	float GetAtkCoef() { return _atkCoef; }

	void SetSkillID(SkillID id) { _id = id; }
	SkillID GetSkillID() { return _id; }

	virtual void SkillLevelUP() 
	{ 
		if (_skillLevel > 5) return;
		_skillLevel++; 
		_atkCoef += 0.1f;
		SetDamage();
	}

	void AddSkillObject(Actor* actor);
	void RemoveSkillObject(Actor* actor);

protected:
	float	_coolTime = 1.f;
	float	_sumTime = 0.f;

	SkillID _id = SkillID::ID_None;
	int32	_skillLevel = 1;
	float	_damage = 0.f;
	float	_atkCoef = 1.1f;

	vector<Actor*>				_skillObjects = {};
	vector<pair<Actor*, float>> _skillObjectsAndDurations = {};
};

