#pragma once
#include "FlipbookActor.h"

class Flipbook;
class Sprite;
class Actor;

enum class PlayerState
{
	Idle,
	Move,
	Attack
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

	void SetState(PlayerState state) 
	{ 
		_state = state; 
		UpdateAnimation();
	}
	void SetDir(Dir dir) 
	{ 
		_dir = dir; 
		UpdateAnimation();
	}

	void	UpdateDir();
	void	UpdateAnimation();

	void	ShootArrow();

private:
	PlayerState	_state = PlayerState::Idle;
	Dir			_dir = Dir::DIR_RIGHT;
	Sight		_sight = Sight::Right;
	Vec2		_speed = {};
	bool		_keyPressed = false;
	Vec2Int		_cellPos = {};
	float		_coolTime = 2.f;
	float		_sumTime = 0.f;

	Flipbook*	_flipbookIdle[2] = {};
	Flipbook*	_flipbookMove[2] = {};
	Flipbook*	_flipbookAttack[2] = {};

	vector<Actor*>	_skills;
};

