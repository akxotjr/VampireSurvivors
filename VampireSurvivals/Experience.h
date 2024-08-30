#pragma once
#include "SpriteActor.h"

class Sprite;
class Collider;

class Experience : public SpriteActor
{
	using Super = SpriteActor;
public:
	Experience();
	virtual ~Experience() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetEXP(int32 exp) { _exp = exp; }
	int32 GetEXP() { return _exp; }

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other) override;

protected:
	vector<Sprite*> _spriteEXP[3] = {};
	int32 _exp = 30;

	bool _takenEXP = false;
};

