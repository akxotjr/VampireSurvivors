#pragma once
#include "Scene.h"
#include "Monster.h"
#include "Slime.h"
#include "Goblin.h"
#include "Orc.h"
#include "Cyclops.h"
#include "WolfRider.h"
#include "Owlbear.h"
#include "Ogre.h"
#include "Player.h"

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
	Vec2 MonsterRandomPos();

	void HandleWave();
	template <typename Ty>
	void CreateMonster()
	{
		unique_ptr<Ty> monster = make_unique<Ty>();
		monster->SetPos(MonsterRandomPos());
		monster->Init();
		AddActor(::move(monster));
	}

	Player* GetPlayer() 
	{
		return dynamic_cast<Player*>(_actors[LAYER_PLAYER].front().get());
	}

	vector<unique_ptr<Actor>>& GetMonsters() 
	{
		return _actors[LAYER_MONSTER];
	}

	bool CanGo(Vec2 dir);


	//void Timer();

protected:
	float _sumTime = 0.f;
	float _spawnCoolTime = 2.f;
	float _spawnSumTime = 0.f;

	std::array<std::function<void(void)>, static_cast<size_t>(MonsterID::ID_Count)> MonsterBuilder = {
		[this]() { CreateMonster<Slime>(); },
		[this]() { CreateMonster<Goblin>(); },
		[this]() { CreateMonster<Orc>(); },
		[this]() { CreateMonster<Cyclops>(); },
		[this]() { CreateMonster<WolfRider>(); },
		[this]() { CreateMonster<Owlbear>(); },
		[this]() { CreateMonster<Ogre>(); },
		//[this]() { return CreateMonster<Dragon>(); },
	};

	bool _firstEpicMonster = false;
	bool _secondEpicMonster = false;
};

