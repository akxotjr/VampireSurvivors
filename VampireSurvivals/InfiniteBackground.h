#pragma once
#include "Background.h"

class InfiniteBackground : public Background
{
	using Super = Background;
public:
	InfiniteBackground();
	virtual ~InfiniteBackground() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;


};

