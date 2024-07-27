#pragma once
#include "Actor.h"

enum class PlayerState
{
	Idle,
	Move,
	Skill
};

class Player : public Actor
{
	using Super = Actor;

public:
	Player();
	virtual ~Player();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetState(PlayerState state) { _state = state; }
	void SetDir(Dir dir) { _dir = dir; }

	void UpdateIdle();
	void UpdateMove();

private:
	PlayerState	_state = PlayerState::Idle;
	Dir			_dir = Dir::DIR_DOWN;
	Vec2		_speed = {};
	bool		_keyPressed = false;
	Vec2Int		_cellPos = {};

};

