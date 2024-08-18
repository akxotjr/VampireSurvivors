#pragma once
#include "Actor.h"

class Flipbook;

class FlipbookActor : public Actor
{
	using Super = Actor;
public:
	FlipbookActor();
	virtual ~FlipbookActor() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetFlipbook(Flipbook* flipbook) 
	{
		if (flipbook && _flipbook == flipbook)
			return;

		_flipbook = flipbook;
		Reset();
	}

	void Reset()
	{
		_sumTime = 0.f;
		_idx = 0;
	}

	float GetFlipbookDuration();

	using AnimationFinishedCallback = ::function<void()>;

	void SetAnimationFinishedCallback(AnimationFinishedCallback callback)
	{
		_animationFinishedCallback = callback;
	}

protected:
	Flipbook*	_flipbook = nullptr;
	float		_sumTime = 0.f;
	int32		_idx = 0;

	AnimationFinishedCallback _animationFinishedCallback = nullptr;
};

