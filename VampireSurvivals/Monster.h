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

protected:
	MonsterState	_state = MonsterState::Idle;
	bool			_isAnimationPlaying = false;
	float			_animationTime = 0.0f;

	Dir				_dir = Dir::DIR_RIGHT;
	Sight			_sight = Sight::Right;
	Vec2			_speed = {};
	float			_coolTime = 2.f;
	float			_sumTime = 0.f;

	Flipbook*	_flipbookIdle[2] = {};
	Flipbook*	_flipbookMove[2] = {};
	Flipbook*	_flipbookAttack[2] = {};
	Flipbook*	_flipbookHurt[2] = {};
	Flipbook*	_flipbookDeath[2] = {};
};

