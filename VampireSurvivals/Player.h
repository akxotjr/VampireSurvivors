#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	Player();
	virtual ~Player();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);
};

