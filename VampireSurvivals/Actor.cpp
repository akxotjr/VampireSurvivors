#include "pch.h"
#include "Actor.h"
#include "Component.h"
#include "Collider.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::Init()
{
	for (auto& components : _components)
		for (auto& component : components)
			component->Init();
}

void Actor::Update()
{
	for (auto& components : _components)
		for (auto& component : components)
			component->Update();
}

void Actor::Render(HDC hdc)
{
	for (auto& components : _components)
		for (auto& component : components)
			component->Render(hdc);
}

void Actor::AddComponent(unique_ptr<Component> component)
{
	if (component == nullptr)
		return;

	_components[component->GetComponentType()].push_back(::move(component));
}

void Actor::RemoveComponent(Component* component)
{
	if (component == nullptr) return;

	auto& components = _components[component->GetComponentType()];
	components.erase(::remove_if(components.begin(), components.end(),
		[&component](const unique_ptr<Component>& ptr) {
			return ptr.get() == component;
		}),
		components.end());
}

vector<unique_ptr<Component>>& Actor::GetColliders()
{
	return _components[COLLIDER];
}



void Actor::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (_skill2MonsterCallback)
	{
		_skill2MonsterCallback(other);
	}
	else if (_skill2PlayerCallback)
	{
		_skill2PlayerCallback(other);
	}
}

void Actor::OnComponentEndOverlap(Collider* collider, Collider* other)
{

}
