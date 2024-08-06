#pragma once
#include "Component.h"

class BoxCollider;
class SphereCollider;

class Collider : public Component
{
public:
	Collider(ColliderType colliderType);
	virtual ~Collider() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other);

	ColliderType GetColliderType() { return _colliderType; }
	void SetShowDebug(bool show) { _showDebug = show; }

	void SetCollisionLayer(COLLISION_LAYER_TYPE layer) { _collisionLayer = layer; }
	COLLISION_LAYER_TYPE GetCollisionLayer() { return _collisionLayer; }

	void ResetCollisionFlag() { _collisionFlag = 0; }
	void AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
	{
		_collisionFlag |= (1 << layer);
	}
	void RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
	{
		_collisionFlag &= ~(1 << layer);
	}
	void SetCollisionFlag(uint32 flag) { _collisionFlag = flag; }
	uint32 GetCollisionFlag() { return _collisionFlag; }


protected:
	ColliderType	_colliderType;
	bool			_showDebug;

	COLLISION_LAYER_TYPE	_collisionLayer = CLT_OBJECT;
	uint32					_collisionFlag = 0xFFFFFFFF;
};

