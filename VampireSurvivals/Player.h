#pragma once
#include "FlipbookActor.h"

class Flipbook;
class Sprite;
class Actor;
class Skill;

enum class PlayerState
{
	Idle,
	Move,
	Attack,
	Hurt,
	Death
};


class Player : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	Player();
	virtual ~Player();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetState(PlayerState state);
	void SetDir(Dir dir) 
	{ 
		_dir = dir; 
		UpdateAnimation();
	}

	void	UpdateDir();
	void	UpdateAnimation();
	void	OnAnimationFinished();

	float	GetAttackPower() { return _stat.AttackPower; }

	bool	TakeDamage(int32 damage);

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other) override;

	// skills
	void AddSkill(Skill* skill) { _skills.push_back(skill); }

	void UseSkill(float deltaTime);
	void UpdateSkill();

private:
	PlayerState	_state = PlayerState::Idle;
	bool		_isAnimationPlaying = false;
	float		_animationTime = 0.0f;

	Dir			_dir = Dir::DIR_RIGHT;
	Sight		_sight = Sight::Right;
	Vec2		_speed = {};
	bool		_keyPressed = false;
	Vec2Int		_cellPos = {};

	float		_coolTime = 2.f;
	float		_sumTime = 0.f;

	Stat		_stat = {};

	Flipbook*	_flipbookIdle[2] = {};
	Flipbook*	_flipbookMove[2] = {};
	Flipbook*	_flipbookAttack[2] = {};
	Flipbook*	_flipbookHurt[2] = {};
	Flipbook*	_flipbookDeath[2] = {};

	vector<Skill*>	_skills;
};

