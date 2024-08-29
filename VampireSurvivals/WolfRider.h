#pragma once
#include "Monster.h"
class WolfRider : public Monster
{
	using Super = Monster;
public:
	WolfRider();
	virtual ~WolfRider() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

