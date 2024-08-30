#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"

unique_ptr<CollisionManager> CollisionManager::instance = nullptr;

void CollisionManager::Init()
{

}

void CollisionManager::Update()
{
	vector<Collider*>& colliders = _colliders;

	for (int32 i = 0; i < colliders.size(); i++)
	{
		for (int32 j = i + 1; j < colliders.size(); j++)
		{
			Collider* src = colliders[i];
			Collider* dest = colliders[j];

			if (src == nullptr || dest == nullptr)
			{
				continue;
			}

			if (src->CheckCollision(dest))
			{
				if (src->_collisionMap.contains(dest) == false)
				{
					src->GetOwner()->OnComponentBeginOverlap(src, dest);
					dest->GetOwner()->OnComponentBeginOverlap(dest, src);
					if (src == nullptr || dest == nullptr || src->GetOwner() == nullptr || dest->GetOwner() == nullptr)
					{
						continue;
					}

					src->_collisionMap.insert(dest);
					dest->_collisionMap.insert(src);
				}
			}
			else
			{
				if (src->_collisionMap.contains(dest))
				{
					src->GetOwner()->OnComponentEndOverlap(src, dest);
					dest->GetOwner()->OnComponentEndOverlap(dest, src);
					src->_collisionMap.erase(dest);
					dest->_collisionMap.erase(src);
				}
			}
		}
	}

	//for (Collider* collider : _collidersToRemove) {
	//	auto it = std::remove(_colliders.begin(), _colliders.end(), collider);
	//	_colliders.erase(it, _colliders.end());
	//}

}




void CollisionManager::AddCollider(Collider* collider)
{
	_colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(Collider* collider)
{
	auto it = std::remove(_colliders.begin(), _colliders.end(), collider);
	_colliders.erase(it, _colliders.end());
}