#include "pch.h"
#include "Skill.h"

Skill::Skill()
{
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

void Skill::AddSkillObjectAndDuration(Actor* actor, float duration)
{
	if (actor == nullptr)
		return;

	_skillObjectsAndDurations.push_back(make_pair(actor, duration));
}

void Skill::RemoveSkillObjectAndDuration(Actor* actor, float duration)
{
	if (actor == nullptr)
		return;

	auto newEnd = std::remove_if(_skillObjectsAndDurations.begin(), _skillObjectsAndDurations.end(),
		[actor, duration](const std::pair<Actor*, float>& elem) {
			return elem.first == actor && elem.second == duration;
		});

	_skillObjectsAndDurations.erase(newEnd, _skillObjectsAndDurations.end());
}
