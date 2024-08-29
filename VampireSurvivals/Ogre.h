#pragma once
#include "Monster.h"

class Ogre : public Monster
{
	using Super = Monster;
public:
	Ogre();
	virtual ~Ogre() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

