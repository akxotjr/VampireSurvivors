#pragma once
#include "Monster.h"

class Slime : public Monster
{
	using Super = Monster;
public:
	Slime();
	virtual ~Slime() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

