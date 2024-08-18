#pragma once
#include "Skill.h"

class Flipbook;

class Iceburst : public Skill
{
public:
	Iceburst();
	virtual ~Iceburst();

	virtual void Init();
	virtual void Update() {}
	virtual void Render(HDC hdc) {}

	virtual void Use(float deltaTime) override;

	virtual void SetDamage() override;

	void OnAnimationFinished();

protected:
	Flipbook* _flipbook = nullptr;

	bool		_isAnimationPlaying = false;
	float		_animationTime = 0.0f;
};

