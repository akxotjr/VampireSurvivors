#pragma once
#include "Monster.h"

class Goblin : public Monster
{
	using Super = Monster;
public:
	Goblin();
	virtual ~Goblin() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

