#pragma once
#include "SpriteActor.h"

class Background : public SpriteActor
{
	using Super = SpriteActor;
public:
	Background();
	virtual ~Background() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

