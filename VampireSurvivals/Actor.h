#pragma once

class Component;
class Collider;

class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	Vec2 GetPos() const { return _pos; }
	void SetPos(Vec2 pos) { _pos = pos; }

	Vec2 GetStartPos() { return _startPos; }
	void SetStartPos(Vec2 pos) { _startPos = pos; }

	Vec2 GetDestPos() { return _destPos; }
	void SetDestPos(Vec2 pos) { _destPos = pos; }

	Vec2 GetDir() 
	{   
		_dir = _destPos - _startPos;
		_dir.Normalize();
		return _dir; 
	}
	void SetDir(Vec2 rotate) { _dir = rotate; }

	LAYER_TYPE GetLayer() { return _layer; }
	void SetLayer(LAYER_TYPE layer) { _layer = layer; }

	void AddComponent(unique_ptr<Component> component);
	void RemoveComponent(Component* component);

	vector<unique_ptr<Component>>& GetColliders();

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

	using Skill2MonsterCallback = ::function<void(Collider*)>;
	using Skill2PlayerCallback = ::function<void(Collider*)>;

	void SetSkill2MonsterCallback(Skill2MonsterCallback callback)
	{
		_skill2MonsterCallback = callback;
	}
	void SetSkill2PlayerCallback(Skill2PlayerCallback callback)
	{
		_skill2PlayerCallback = callback;
	}

protected:
	Vec2			_pos = { 0, 0 };
	Vec2			_startPos = { 0, 0 };
	Vec2			_destPos = { 0, 0 };
	Vec2			_dir = { 0,0 };
	LAYER_TYPE		_layer = LAYER_BACKGROUND;

	vector<unique_ptr<Component>> _components[COMPONENT_TYPE_COUNT];

	Skill2MonsterCallback	_skill2MonsterCallback = nullptr;
	Skill2PlayerCallback	_skill2PlayerCallback = nullptr;
};

