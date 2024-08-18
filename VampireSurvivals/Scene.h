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

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	void AddUI(UI* ui);
	void RemmoveUI(UI* ui);

	Vec2 GetPlayerPos();

	const vector<Actor*> GetMonsters()
	{
		return _actors[LAYER_MONSTER];
	}

public:
	vector<Actor*> _actors[LAYER_MAXCOUNT];
	vector<UI*>		_uis;
};

