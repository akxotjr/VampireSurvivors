#pragma once

class Component;

class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	Vec2 GetPos() { return _pos; }
	void SetPos(Vec2 pos) { _pos = pos; }

	Vec2 GetDestPos() { return _destPos; }
	void SetDestPos(Vec2 pos) { _destPos = pos; }

	Vec2 GetDir() { return _dir; }
	void SetDir(Vec2 rotate) { _dir = rotate; }

	LAYER_TYPE GetLayer() { return _layer; }
	void SetLayer(LAYER_TYPE layer) { _layer = layer; }

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

protected:
	Vec2			_pos = { 0, 0 };
	Vec2			_destPos = { 0, 0 };
	Vec2			_dir = { 0,0 };
	LAYER_TYPE		_layer = LAYER_BACKGROUND;
	
	vector<Component*> _components;
};

