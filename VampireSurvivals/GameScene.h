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

	void AddColliders(Collider* collider);
	void RemoveColliders(Collider* collider);

protected:
	float _sumTime = 0.f;
	float _coolTime = 3.f; // monster respawn cool time

public:
	vector<Collider*> _colliders[CLT_MAX_COUNT];
};

