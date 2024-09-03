#pragma once
#include "Panel.h"

class Sprite;

class SelectSkillPanel : public Panel
{
	using Super = Panel;
public:
	SelectSkillPanel();
	virtual ~SelectSkillPanel();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void RemoveAllChild();

	void SetFinished() { _finished = true; }

private:
	Sprite* _sprite = nullptr;
	float	_sumTime = 0.f;

	bool	_finished = false;
};

