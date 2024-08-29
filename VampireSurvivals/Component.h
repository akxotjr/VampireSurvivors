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

	//weak_ptr<Actor> GetOwner() { return _owner; }
	//void SetOwner(weak_ptr<Actor> owner) { _owner = owner; }
	void SetOwner(Actor* owner) { _owner = owner; }
	Actor* GetOwner() { return _owner; }

	void SetComponentType(COMPONENT_TYPE type) { _type = type; }
	COMPONENT_TYPE GetComponentType() { return _type; }

protected:
	COMPONENT_TYPE _type;
	//weak_ptr<Actor> _owner;
	Actor* _owner;
};

