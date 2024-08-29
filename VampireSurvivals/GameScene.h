#pragma once
#include "Scene.h"

class Collider;
class Monster;

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
	Vec2 MonsterRandomPos();

	//void SpawnMonster(MonsterID id);
	//void HandleWave();

protected:
	float _sumTime = 0.f;
	float _coolTime = 3.f; // monster respawn cool time

	float _spawnCoolTime = 2.f;
	float _spawnSumTime = 0.f;
};

