#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Flipbook.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "DevScene.h"
#include "GameScene.h"
#include "CameraComponent.h"
#include "Projectile.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Monster.h"
#include "Experience.h"
#include "SelectSkillPanel.h"
#include "Button.h"
#include "Sprite.h"

Player::Player()
{
	_stat = { 100, 100, 50 };


	SetLayer(LAYER_PLAYER);


	_flipbookIdle[DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerIdleUp");
	_flipbookIdle[DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerIdleDown");
	_flipbookIdle[DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerIdleLeft");
	_flipbookIdle[DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerIdleRight");

	_flipbookAttack[DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerAttackUp");
	_flipbookAttack[DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerAttackDown");
	_flipbookAttack[DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerAttackLeft");
	_flipbookAttack[DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerAttackRight");

	_flipbookMove[DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerMoveUp");
	_flipbookMove[DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerMoveDown");
	_flipbookMove[DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerMoveLeft");
	_flipbookMove[DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerMoveRight");

	_flipbookHurt[DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerHurtUp");
	_flipbookHurt[DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerHurtDown");
	_flipbookHurt[DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerHurtLeft");
	_flipbookHurt[DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerHurtRight");

	_flipbookDeath[DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerDeathUp");
	_flipbookDeath[DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerDeathDown");
	_flipbookDeath[DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerDeathLeft");
	_flipbookDeath[DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SwashbucklerDeathRight");

	unique_ptr<CameraComponent> camera = make_unique<CameraComponent>();
	camera->SetOwner(this);
	_cmr = camera.get();
	AddComponent(::move(camera));

	unique_ptr<SphereCollider> collider = make_unique<SphereCollider>();
	collider->SetOwner(this);
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->ResetCollisionFlag();
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_MONSTER);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_MONSTER_SKILL);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_MONSTER_ATK_RANGE);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_EXP);
	collider->SetRadius(20);
	CollisionManager::GetInstance()->AddCollider(collider.get());
	AddComponent(::move(collider));

	SkillBuilder[SkillID::ID_Slash]();
}

Player::~Player()
{
}

void Player::Init()
{
	Super::Init();
	SetState(PlayerState::Idle);
}

void Player::Update()
{
	//if (_pause) return;
	Super::Update();

	float deltaTime = TimeManager::GetInstance()->GetAdjustDeltaTime();
	if (deltaTime == 0) return;

	_sumTime += deltaTime;
	UseSkill(deltaTime);

	if (_sumTime > _coolTime)
	{
		if (_sumTime > _coolTime + 0.5f)
		{
			SetState(PlayerState::Attack);
			_sumTime = 0.f;

		}
	}

	Vec2 dir = UpdateDir();
	if (dir == Vec2(0,0))
	{
		SetState(PlayerState::Idle);
	}
	else
	{
		_pos += dir * _speed;
		SetState(PlayerState::Move);
	}
	UpdateAnimation();

	UpdateSkill();
	_cmr->Update();
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
	Utils::DrawHP(hdc, Vec2(480, 340), 30, 5, _stat.HP / _stat.MaxHP);

}

void Player::SetState(PlayerState state)
{
	if (!_isAnimationPlaying)
	{
		_state = state;
	}
}

Vec2 Player::UpdateDir()
{
	Vec2 dir = { 0,0 };

	if (InputManager::GetInstance()->GetButton(KeyType::W))
	{
		dir += {0, -1};
		_dir = Dir::DIR_UP;
	}
	else if (InputManager::GetInstance()->GetButton(KeyType::S))
	{
		dir += {0, 1};
		_dir = Dir::DIR_DOWN;
	}

	if (InputManager::GetInstance()->GetButton(KeyType::D))
	{
		dir += {1, 0};
		_dir = Dir::DIR_RIGHT;
	}
	else if (InputManager::GetInstance()->GetButton(KeyType::A))
	{
		dir += {-1, 0};
		_dir = Dir::DIR_LEFT;
	}

	GameScene* scene = static_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	if (scene->CanGo(dir))
	{
		dir.Normalize();
		return dir;
	}
	return { 0,0 };
}

void Player::UpdateAnimation()
{
	if (!_isAnimationPlaying)
	{
		switch (_state)
		{
		case PlayerState::Idle:
			if (_keyPressed)
				SetFlipbook(_flipbookMove[_dir]);
			else
				SetFlipbook(_flipbookIdle[_dir]);
			break;
		case PlayerState::Move:
			SetFlipbook(_flipbookMove[_dir]);
			break;
		case PlayerState::Attack:
			SetFlipbook(_flipbookAttack[_dir]);
			_isAnimationPlaying = true;
			_animationTime = 0.0f;
			break;
		case PlayerState::Hurt:
			SetFlipbook(_flipbookHurt[_dir]);
			_isAnimationPlaying = true;
			_animationTime = 0.0f;
			break;
		case PlayerState::Death:
			SetFlipbook(_flipbookDeath[_dir]);
			_isAnimationPlaying = true;
			_animationTime = 0.0f;
			break;
		}
	}
	else
	{
		_animationTime += TimeManager::GetInstance()->GetAdjustDeltaTime();
		if (_animationTime >= GetFlipbookDuration())
		{
			OnAnimationFinished();
		}
	}
}

void Player::OnAnimationFinished()
{
	_isAnimationPlaying = false;
	SetState(PlayerState::Idle);
}


bool Player::TakeDamage(int32 damage)
{
	_stat.HP -= damage;

	if (_stat.HP > 0)
		return false;
	return true;
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (other->GetCollisionLayer() == CLT_MONSTER)
	{
		Monster* monster = static_cast<Monster*>(other->GetOwner());
		if (!TakeDamage(monster->GetDamage()))
			SetState(PlayerState::Hurt);
		else
			SetState(PlayerState::Death);
	}
	else if (other->GetCollisionLayer() == CLT_MONSTER_SKILL)
	{

	}
}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{

}

void Player::UseSkill(float deltaTime)
{
	for (auto& skill : _skills)
		skill->Use(deltaTime);
}

void Player::UpdateSkill()
{
	for (auto& skill : _skills)
		skill->Update();
}

void Player::TakeEXP(int32 exp)
{
	_exp += exp;
	if (_exp >= _maxExp)
	{
		int32 overExp = _exp - _maxExp;
		_exp = overExp;

		_maxExp += 20;

		LevelUP();
	}
}

void Player::LevelUP()
{
	_pause = true;
	_level++;
	TimeManager::GetInstance()->SetTimeScale(0.f);

	GameScene* scene = static_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
	unique_ptr<SelectSkillPanel> ssp = make_unique<SelectSkillPanel>();
	ssp->Init();

	scene->AddUI(::move(ssp));
}

pair<int32, int32> Player::RandomSkill()
{
	int32 possibleSkills = (1 << 5) - 1;
	int32 selectedSkills = 0;

	if (_skills.size() == 4)
	{
		possibleSkills = 0;
		for (auto& skill : _skills)
		{
			possibleSkills |= (1 << skill->GetSkillID());
		}
	}
	for (auto& skill : _skills)
	{
		if (skill->GetSkillLevel() == 5)
		{
			possibleSkills &= ~(1 << skill->GetSkillID());
		}
	}

	::random_device rd;
	::mt19937 gen(rd());

	::uniform_int_distribution<int32> dist(0, 5);

	int32 count = 0; 
	
	while (count < 3 && possibleSkills > 0)
	{
		int32 i = dist(gen);

		if (possibleSkills & (1 << i))
		{
			selectedSkills |= (1 << i);
			possibleSkills &= ~(1 << i);
			count++;
		}
	}

	return make_pair(selectedSkills, count);
}



void Player::SkillLevelUP(SkillID id, SelectSkillPanel* panel)
{
	bool flag = false;
	for (int32 i = 0; i < _skills.size(); i++)
	{
		if (_skills[i]->GetSkillID() == id)
		{
			_skills[i]->SkillLevelUP();
			_skillIDnLevel[i].second++;

			flag = true;
			break;
		}
	}

	if (!flag)
	{
		SkillBuilder[id]();
	}
	EventManager::GetInstance()->AddEvent([panel]() {
		GameScene* scene = static_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
		scene->RemoveUI(panel);
		});

	TimeManager::GetInstance()->SetTimeScale(1.f);
}




