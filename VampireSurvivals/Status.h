#pragma once
#include "Panel.h"

class Sprite;
class Player;

enum 
{
	HP = 0,
	EXP,
};

class Status : public Panel
{
	using Super = Panel;
public:
	Status();
	virtual ~Status();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

protected:
	Sprite* _hpBar = nullptr;
	Sprite* _expBar = nullptr;
	Sprite* _levelToken = nullptr;
	Sprite* _skillIcon[SkillID::ID_Count];
	
	Player* _player = nullptr;
	vector<pair<SkillID, int32>> _skillIDnLevel;

	Vec2Int _hpSize = {};
	Vec2Int _expSize = {};
};

