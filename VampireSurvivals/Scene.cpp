#include "pch.h"
#include "Scene.h"
#include "Actor.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Init()
{
	//for (const vector<shared_ptr<Actor>>& actors : _actors)
	//	for (shared_ptr<Actor> actor : actors)
	//		actor->Init();
	for (const vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->Init();
}

void Scene::Update()
{
	//for (const vector<shared_ptr<Actor>>& actors : _actors)
	//	for (shared_ptr<Actor> actor : actors)
	//		actor->Update();
	for (const vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->Update();
}

void Scene::Render(HDC hdc)
{
	//for (const vector<shared_ptr<Actor>>& actors : _actors)
	//	for (shared_ptr<Actor> actor : actors)
	//		actor->Render(hdc);
	for (const vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->Render(hdc);
}

//void Scene::AddActor(shared_ptr<Actor> actor)
//{
//	if (actor == nullptr)
//		return;
//
//	_actors[actor->GetLayer()].push_back(actor);
//}
//
//void Scene::RemoveActor(shared_ptr<Actor> actor)
//{
//	if (actor == nullptr)
//		return;
//
//	vector<shared_ptr<Actor>>& v = _actors[actor->GetLayer()];
//	v.erase(std::remove(v.begin(), v.end(), actor), v.end());
//}


void Scene::AddActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	_actors[actor->GetLayer()].push_back(actor);
}

void Scene::RemoveActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	vector<Actor*>& v = _actors[actor->GetLayer()];
	v.erase(std::remove(v.begin(), v.end(), actor), v.end());

//	delete(actor);
}

Vec2 Scene::GetPlayerPos()
{
	if (_actors[LAYER_PLAYER].size() == 0)
		return { 0,0 };
	else
		return _actors[LAYER_PLAYER].front()->GetPos();
}
