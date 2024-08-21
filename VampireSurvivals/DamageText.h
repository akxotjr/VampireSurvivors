#pragma once
#include "Actor.h"

class DamageText : public Actor
{
public:
	DamageText();
	virtual ~DamageText();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetText(int32 damagevalue) 
	{ 
		_text = to_wstring(damagevalue); 
	}

private:
	wstring		_text;
	float		_lifetime = 1.f;
	float		_elapsedTime = 0.f;
};

