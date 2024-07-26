#pragma once

class Actor;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void AddActor(shared_ptr<Actor> actor);
	void RemoveActor(shared_ptr<Actor> actor);

public:
	vector<shared_ptr<Actor>> _actors[LAYER_MAXCOUNT];
	//vector<UI*>		_uis;
};

