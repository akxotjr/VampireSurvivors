#pragma once
#include "Panel.h"

class Sprite;

class SelectSkillPanel : public Panel
{
	using Super = UI;
public:
	SelectSkillPanel();
	virtual ~SelectSkillPanel();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void RemoveAllChild();

private:
	Sprite* _sprite = nullptr;
	float	_sumTime = 0.f;
};

