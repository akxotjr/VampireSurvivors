#include "pch.h"
#include "Slash.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "SpriteActor.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "Projectile.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameScene.h"
#include "Player.h"

Slash::Slash()
{
#pragma region Sprites
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash00"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash01"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash02"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash03"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash04"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash05"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash06"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash07"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash08"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash09"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash10"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash11"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash12"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash13"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash14"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash15"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash16"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash17"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash18"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash19"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash20"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash21"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash22"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash23"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash24"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash25"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash26"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash27"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash28"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash29"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash30"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash31"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash32"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash33"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash34"));
	_sprites.push_back(ResourceManager::GetInstance()->GetSprite(L"Slash35"));
#pragma endregion
}

Slash::~Slash()
{
}

void Slash::Init()
{
	SetDamage();
}

void Slash::Use(float deltaTime)
{
	_sumTime += deltaTime;

	if (_sumTime >= _coolTime)
	{
		Vec2 mousePos = {};
		mousePos.x = InputManager::GetInstance()->GetMousePos().x;
		mousePos.y = InputManager::GetInstance()->GetMousePos().y;
		Vec2 attackDir = mousePos - Vec2(480, 360);
		attackDir.Normalize();

		int32 currentSector = GetDegreeSector(attackDir);

		int32 slashCount = _skillLevel * 2 - 1;
		const vector<pair<int32, Vec2>>& attackSectorsAndDirs = GetAttackSectorsAndDirs(currentSector, attackDir);

		for (int32 i = 0; i < slashCount; i++)
		{
			Projectile* slash = new Projectile();
			slash->SetSprite(_sprites[attackSectorsAndDirs[i].first]);
			slash->SetPos(_owner->GetPos());
			slash->SetDestPos(attackSectorsAndDirs[i].second);
			slash->SetDir(attackSectorsAndDirs[i].second);
			slash->SetDamage(_damage);

			GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
			scene->AddActor(slash);
		}

		_sumTime = 0.f;
	}
	else
		return;
}

void Slash::SetDamage()
{
	Player* player = dynamic_cast<Player*>(GetOwner());
	float atk = player->GetAttackPower();

	_damage = atk * _atkCoef;
}

int32 Slash::GetDegreeSector(Vec2 dir)
{
	float theta = atan2(dir.y, dir.x);

	float degree = theta * (180 / PI);
	if (degree < 0)
		degree += 360;

	int32 sector = static_cast<int>(degree / 10.0);
	
	return 35 - sector;
}

vector<pair<int32, Vec2>> Slash::GetAttackSectorsAndDirs(int currentSector, Vec2 currentDir)
{
	vector<pair<int32, Vec2>> sectorsAndDirs;

	int32 range = _skillLevel - 1;

	for (int32 i = -range; i <= range ; i++)
	{
		Vec2 dir;
		dir.x = currentDir.x * cos(i * 10 * (PI / 180)) - currentDir.y * sin(i * 10 * (PI / 180));
		dir.y = currentDir.x * sin(i * 10 * (PI / 180)) + currentDir.y * cos(i * 10 * (PI / 180));

		int32 sector = GetDegreeSector(dir);
		sectorsAndDirs.push_back(make_pair(sector, dir));
	}

	return sectorsAndDirs;
}

