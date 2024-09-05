#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "UI.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Init()
{
	for (auto& actors : _actors)
		for (auto& actor : actors)
			actor->Init();

	for (auto& ui : _uis)
		ui->Init();
}

void Scene::Update()
{
	for (auto& actors : _actors)
		for (auto& actor : actors)
		{
			if (actor.get() == nullptr || _finished)
			{
				return;
			}
			actor->Update();
		}
	for (auto& ui : _uis)
	{
		if (ui.get() == nullptr || _finished)
		{
			return;
		}
		ui->Update();

	}
		
}

void Scene::Render(HDC hdc)
{
	for (auto& actors : _actors)
		for (auto& actor : actors)
			actor->Render(hdc);

	for (auto& ui : _uis)
		ui->Render(hdc);
}


void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	if (actor == nullptr)
		return;

	_actors[actor->GetLayer()].push_back(::move(actor));
}


void Scene::RemoveActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	auto& v = _actors[actor->GetLayer()];
	v.erase(::remove_if(v.begin(), v.end(),
		[&actor](const unique_ptr<Actor>& ptr) {
			return ptr.get() == actor;  
		}),
		v.end());
}

void Scene::AddUI(unique_ptr<UI> ui)
{
	if (ui == nullptr)
		return;

	_uis.push_back(::move(ui));
}

void Scene::RemoveUI(UI* ui)
{
	if (ui == nullptr)
		return;

	_uis.erase(::remove_if(_uis.begin(), _uis.end(),
		[&ui](const unique_ptr<UI>& ptr) {
			return ptr.get() == ui;
		}),
		_uis.end());
}

Vec2 Scene::GetPlayerPos()
{
	if (_actors[LAYER_PLAYER].empty())
		return { 0,0 };
	else
		return _actors[LAYER_PLAYER].front()->GetPos();
}
