#pragma once

#include "Actor.h"

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	weak_ptr<Actor> GetOwner() { return _owner; }
	void SetOwner(weak_ptr<Actor> owner) { _owner = owner; }

protected:
	weak_ptr<Actor> _owner;
};

