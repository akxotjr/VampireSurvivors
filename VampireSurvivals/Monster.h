#pragma once
#include "FlipbookActor.h"

enum class MonsterState
{
	Idle,
	Move,
	Attack,
	Hurt,
	Death
};

enum class MonsterGrade
{
	Normal,
	Rare,
	Epic,
	Boss
};

class Flipbook;

class Monster : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	Monster();
	virtual ~Monster() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetState(MonsterState state);
	void SetDir(Dir dir)
	{
		_dir = dir;
		UpdateAnimation();
	}

	void UpdateAnimation();
	void OnAnimationFinished();

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other) override;

	bool TakeDamage(float damage);

	int32 GetDamage()
	{
		return _stat.AttackPower;
	}

	void SetGrade(MonsterGrade grade) { _grade = grade; }
	MonsterGrade GetGrade() { return _grade; }


protected:
	MonsterState	_state = MonsterState::Idle;
	MonsterGrade	_grade = MonsterGrade::Normal;
	bool			_isAnimationPlaying = false;
	float			_animationTime = 0.0f;

	Dir				_dir = Dir::DIR_RIGHT;
	float			_speed = 0.5f;
	float			_coolTime = 2.f;
	float			_sumTime = 0.f;

	Stat			_stat;

	Flipbook*	_flipbookIdle[Dir::DIR_COUNT] = {};
	Flipbook*	_flipbookMove[Dir::DIR_COUNT] = {};
	Flipbook*	_flipbookAttack[Dir::DIR_COUNT] = {};
	Flipbook*	_flipbookHurt[Dir::DIR_COUNT] = {};
	Flipbook*	_flipbookDeath[Dir::DIR_COUNT] = {};
};

