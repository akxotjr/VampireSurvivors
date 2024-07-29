#pragma once
#include "FlipbookActor.h"

class Flipbook;

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

	void UpdateAnimation();

	void UpdateIdle();
	void UpdateMove();
	void UpdateAttack();

	//void SetCellPos(Vec2Int cellPos, bool teleport = false);
	//bool HasReachedDest();
	//bool CanGo(Vec2Int cellPos);

private:
	PlayerState	_state = PlayerState::Idle;
	Dir			_dir = Dir::DIR_DOWN;
	Vec2		_speed = {};
	bool		_keyPressed = false;
	Vec2Int		_cellPos = {};

	Flipbook*	_flipbookIdle = nullptr;
	Flipbook*	_flipbookMove = nullptr;
	Flipbook*	_flipbookAttack = nullptr;
};

