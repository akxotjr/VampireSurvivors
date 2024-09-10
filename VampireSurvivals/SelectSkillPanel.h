#pragma once
#include "Panel.h"

class Sprite;
class Player;

class SelectSkillPanel : public Panel
{
	using Super = Panel;
public:
	SelectSkillPanel();
	virtual ~SelectSkillPanel();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void RemoveAllChild();

	void SetButtonCnt(int32 count) { _buttonCount = count; }

private:
	float	_sumTime = 0.f;  // 선택 제한 시간

	bool	_finished = false;

	Sprite* _skillButton = nullptr;
	Sprite* _skillIcon[SkillID::ID_Count];
	Sprite* _skillName[SkillID::ID_Count];

	Player* _player = nullptr;

	int32			_buttonCount = 0;
	vector<Vec2>	_buttonPos[3] = 
	{
		{{380, 160}},
		{{180, 160}, {580, 160}},
		{{145, 160}, {380, 160}, {615, 160}}
	};
};

