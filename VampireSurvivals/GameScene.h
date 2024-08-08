#pragma once
#include "Scene.h"

class Collider;

class GameScene : public Scene
{
	using Super = Scene;
public:
	GameScene();
	virtual ~GameScene();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	// monster spawn
	void MonsterRespawn();
	Vec2 MonsterRandomPos(float deltaTime);

protected:
	float _sumTime = 0.f;
	float _coolTime = 3.f; // monster respawn cool time
};

