#pragma once

#include "Actor.h"

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void Init() {}
	virtual void Update() {}
	virtual void Render(HDC hdc) {}

	void SetOwner(Actor* owner) { _owner = owner; }
	Actor* GetOwner() { return _owner; }

	void SetComponentType(COMPONENT_TYPE type) { _type = type; }
	COMPONENT_TYPE GetComponentType() { return _type; }

protected:
	COMPONENT_TYPE _type;
	Actor* _owner;
};

