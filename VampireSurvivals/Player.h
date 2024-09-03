#pragma once
#include "FlipbookActor.h"
#include "Skill.h"
#include "Slash.h"
#include "Iceburst.h"
#include "Lightning.h"
#include "Suriken.h"
#include "ForceField.h"

class Flipbook;
class Sprite;
class Actor;
class SelectSkillPanel;



enum class PlayerState
{
	Idle,
	Move,
	Attack,
	Hurt,
	Death
};

class Player : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	Player();
	virtual ~Player();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetState(PlayerState state);
	void SetDir(Dir dir) 
	{ 
		_dir = dir; 
		UpdateAnimation();
	}

	Vec2	UpdateDir();
	void	UpdateAnimation();
	void	OnAnimationFinished();

	float	GetAttackPower() { return _stat.AttackPower; }

	bool	TakeDamage(int32 damage);

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other) override;

	// skills
	void AddSkill(unique_ptr<Skill> skill) 
	{ 
		_skillIDnLevel.push_back(make_pair(skill->GetSkillID(), 1));
		_skills.push_back(::move(skill)); 
	}

	void UseSkill(float deltaTime);
	void UpdateSkill();

	void TakeEXP(int32 exp);
	void LevelUP();
	void SkillLevelUP(SkillID id, SelectSkillPanel* panel);
	void RandomSkill();
	void GenerateSkillButton(SkillID id, Vec2 pos, SelectSkillPanel* panel);


	template <typename Ty>
	void CreateSkill()
	{
		unique_ptr<Ty> skill = make_unique<Ty>();
		skill->SetOwner(this);
		skill->Init();
		AddSkill(::move(skill));
	}

	float GetHPRate() { return _stat.HP / _stat.MaxHP; }
	float GetEXPRate() { return (float)_exp / (float)_maxExp; }

	vector<pair<SkillID, int32>>& GetSkillIDnSkillLevel() { return _skillIDnLevel; }

private:
	PlayerState	_state = PlayerState::Idle;
	bool		_isAnimationPlaying = false;
	float		_animationTime = 0.0f;

	Dir			_dir = Dir::DIR_DOWN;
	float		_speed = 1.f;
	bool		_keyPressed = false;
	Vec2Int		_cellPos = {};

	float		_coolTime = 2.f;
	float		_sumTime = 0.f;

	int32		_exp = 0;
	int32		_maxExp = 50;
	int32		_level = 1;

	// skillpool 에서 고를 수 있는 skill을 1, 각 i번째 비트는 skill_id가 i임을 의미
	// 켜져있는 i번째 비트가 의미하는것은 skill_id가 i인 스킬을 획득했다는것


	Stat		_stat = {};

	Flipbook*	_flipbookIdle[Dir::DIR_COUNT] = {};	
	Flipbook*	_flipbookAttack[Dir::DIR_COUNT] = {};
	Flipbook*	_flipbookMove[Dir::DIR_COUNT] = {};
	Flipbook*	_flipbookHurt[Dir::DIR_COUNT] = {};
	Flipbook*	_flipbookDeath[Dir::DIR_COUNT] = {};

	vector<unique_ptr<Skill>> _skills;
	vector<pair<SkillID, int32>> _skillIDnLevel;
	vector<wstring> _skillNames = { L"slash", L"iceburst", L"lightning", L"suriken", L"forcefiled" };


	std::array<std::function<void(void)>, SkillID::ID_Count> SkillBuilder = {
		[this]() { CreateSkill<Slash>(); },
		[this]() { CreateSkill<Iceburst>(); },
		[this]() { CreateSkill<Lightning>(); },
		[this]() { CreateSkill<Suriken>(); },
		[this]() { CreateSkill<ForceField>(); },
	};
};

