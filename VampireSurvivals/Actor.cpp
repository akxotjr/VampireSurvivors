#include "pch.h"
#include "Actor.h"
#include "Component.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::Init()
{
	for (Component* component : _components)
	{
		component->Init();
	}
}

void Actor::Update()
{
	for (Component* component : _components)
	{
		component->Update();
	}
}

void Actor::Render(HDC hdc)
{
	for (Component* component : _components)
	{
		component->Render(hdc);
	}
}
