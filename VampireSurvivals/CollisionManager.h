#pragma once

class Collider;

class CollisionManager
{
public:
	~CollisionManager() = default;

	static CollisionManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = make_unique<CollisionManager>();
		}
		return instance.get();
	}

public:
	void Init();
	void Update();

	void AddCollider(Collider* collider);
	void RemoveCollider(Collider* collider);

private:
	CollisionManager() = default;

	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;

	friend std::unique_ptr<CollisionManager> std::make_unique<CollisionManager>();


private:
	static unique_ptr<CollisionManager> instance;

	vector<Collider*> _colliders;
	vector<Collider*> _colliderstoremove;
};

