#pragma once
#include "Monster.h"

class Dragon : public Monster
{
	using Super = Monster;
public:
	Dragon();
	virtual ~Dragon() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// Boss Pattern
	void Dash();
	void FireBreath();


protected:

};

