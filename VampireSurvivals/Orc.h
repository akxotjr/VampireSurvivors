#pragma once
#include "FlipbookActor.h"

//enum class PlayerState
//{
//	Idle,
//	Move,
//	Attack
//};

class Orc : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	Orc();
	virtual ~Orc();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);


private:
	//PlayerState	_state = PlayerState::Idle;
	Dir			_dir = Dir::DIR_DOWN;
	Vec2		_speed = {};
	bool		_keyPressed = false;
	Vec2Int		_cellPos = {};

	Flipbook*	_flipbookIdle = nullptr;
	Flipbook*	_flipbookMove = nullptr;
	Flipbook*	_flipbookAttack = nullptr;
};

