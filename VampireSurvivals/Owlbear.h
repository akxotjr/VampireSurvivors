#pragma once
#include "Monster.h"

class Owlbear : public Monster
{
	using Super = Monster;
public:
	Owlbear();
	virtual ~Owlbear() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

