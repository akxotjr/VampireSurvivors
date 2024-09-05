#pragma once

class Actor;
class UI;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void AddActor(unique_ptr<Actor> actor);
	void RemoveActor(Actor* actor);

	void AddUI(unique_ptr<UI> ui);
	void RemoveUI(UI* ui);

	Vec2 GetPlayerPos();

	const vector<unique_ptr<Actor>>& GetMonsters()
	{
		return _actors[LAYER_MONSTER];
	}

	void SetFinished() { _finished = true; }

public:
	vector<unique_ptr<Actor>>	_actors[LAYER_MAXCOUNT];
	vector<unique_ptr<UI>>		_uis;

protected:
	bool _finished = false;
};

