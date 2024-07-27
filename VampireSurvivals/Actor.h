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

	LAYER_TYPE GetLayer() { return _layer; }
	void SetLayer(LAYER_TYPE layer) { _layer = layer; }



protected:
	Vec2 _pos = { 0, 0 };
	Vec2 _destPos = { 0, 0 };
	LAYER_TYPE _layer = LAYER_OBJECT;
	
	vector<Component*> _components;
};

