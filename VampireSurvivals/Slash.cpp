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
#include "Monster.h"
#include "DamageText.h"
#include "EventManager.h"

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
	SetSkillID(SkillID::ID_Slash);
	SetDamage();
}

void Slash::Use(float deltaTime)
{
	_sumTime += deltaTime;

	GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());


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
			unique_ptr<SpriteActor> slash = make_unique<SpriteActor>();
			slash->SetSprite(_sprites[attackSectorsAndDirs[i].first]);
			slash->SetPos(_owner->GetPos());
			slash->SetDestPos(attackSectorsAndDirs[i].second);
			slash->SetDir(attackSectorsAndDirs[i].second);
			slash->SetLayer(LAYER_SKILL);

			unique_ptr<SphereCollider> collider = make_unique<SphereCollider>();
			collider->SetCollisionLayer(CLT_PLAYER_SKILL);
			collider->ResetCollisionFlag();
			collider->SetCollisionFlag(CLT_MONSTER);
			collider->SetOwner(slash.get());
			collider->SetRadius(15);
			CollisionManager::GetInstance()->AddCollider(collider.get());
			slash->AddComponent(::move(collider));

			slash->SetSkill2MonsterCallback([this, scene](Collider* other) {
				if (other->GetCollisionLayer() == CLT_MONSTER)
				{
					Monster* monster = static_cast<Monster*>(other->GetOwner());
					if (monster)
					{
						if (monster->TakeDamage(GetDamage()))
						{
							monster->SetState(MonsterState::Death);
						}
						else
						{
							monster->SetState(MonsterState::Hurt);
							const float damagevalue = GetDamage();

							//unique_ptr<DamageText> damagetext = make_unique<DamageText>();
							//damagetext->SetPos(monster->GetPos() + Vec2(10, -5));
							//damagetext->SetText(damagevalue);
							//damagetext->SetLayer(LAYER_DAMAGETEXT);

							//scene->AddActor(::move(damagetext));
						}
					}
				}
			});

			Skill::AddSkillObject(slash.get());
			scene->AddActor(::move(slash));
		}

		_sumTime = 0.f;
	}

	{
		for (auto& skillObject : _skillObjects)
		{
			Vec2 pos = skillObject->GetPos();
			Vec2 playerPos = GetOwner()->GetPos();

			if (pos.x > playerPos.x + GWinSizeX / 2 + 32 ||
				pos.x < playerPos.x - GWinSizeX / 2 - 32 ||
				pos.y > playerPos.y + GWinSizeY / 2 + 32 ||
				pos.y < playerPos.y - GWinSizeY / 2 - 32)
			{

				vector<unique_ptr<Component>>& colliders = skillObject->GetColliders();
				for (auto& collider : colliders)
				{
					Collider* col = dynamic_cast<Collider*>(collider.get());
					EventManager::GetInstance()->AddEvent([col]() {
						CollisionManager::GetInstance()->RemoveCollider(col);
						});
				}

				_removeSkillObjects.push_back(skillObject);
			}
			else
			{
				Vec2 dir = skillObject->GetDir();
				skillObject->SetPos(pos + dir * _moveSpeed);
			}
		}
		EventManager::GetInstance()->AddEvent([this, scene]() {
			for (auto& it : _removeSkillObjects)
			{
				RemoveSkillObject(it);
				scene->RemoveActor(it);
			}
			_removeSkillObjects.clear();
			});
	}
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

