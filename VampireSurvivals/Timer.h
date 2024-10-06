#pragma once
#include "Panel.h"

class Font;

class Timer : public Panel
{
	using Super = Panel;
public:
	Timer();
	virtual ~Timer();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

private:
	int32 _minute = 0;
	int32 _second = 0;

	float _sumTime = 0.f;
	Font* _font = nullptr;
};

