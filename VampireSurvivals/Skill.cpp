#include "pch.h"
#include "Skill.h"

Skill::Skill()
{
	SetComponentType(SKILL);
}

Skill::~Skill()
{
}

void Skill::AddSkillObject(Actor* actor)
{
	if (actor == nullptr)
		return;

	_skillObjects.push_back(actor);
}

void Skill::RemoveSkillObject(Actor* actor)
{
	if (actor == nullptr)
		return;

	_skillObjects.erase(std::remove(_skillObjects.begin(), _skillObjects.end(), actor), _skillObjects.end());
}
