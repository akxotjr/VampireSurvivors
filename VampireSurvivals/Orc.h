#pragma once
#include "Monster.h"
class Orc : public Monster
{
	using Super = Monster;
public:
	Orc();
	virtual ~Orc() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

