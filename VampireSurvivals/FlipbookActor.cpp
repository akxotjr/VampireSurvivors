#include "pch.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
#include "Texture.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Scene.h"
#include "Component.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "EventManager.h"

FlipbookActor::FlipbookActor()
{
}

FlipbookActor::~FlipbookActor()
{
}

void FlipbookActor::Init()
{
	Super::Init();
}

void FlipbookActor::Update()
{
	Super::Update();

	if (_flipbook == nullptr) return;

	const FlipbookInfo& info = _flipbook->GetInfo();

	if (info.loop == false && _idx == info.end)
	{
		vector<unique_ptr<Component>>& colliders = GetColliders();
		for (auto& collider : colliders)
		{
			CollisionManager::GetInstance()->RemoveCollider(dynamic_cast<Collider*>(collider.get()));
		}

		GameScene* scene = dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene());
		EventManager::GetInstance()->AddEvent([scene, this]() {
			scene->RemoveActor(this);
			});
		return;
	}

	float deltaTime = TimeManager::GetInstance()->GetAdjustDeltaTime();

	_sumTime += deltaTime;

	int32 frameCount = (info.end - info.start + 1);
	float delta = info.duration / frameCount;

	if (_sumTime >= delta)
	{
		_sumTime = 0.f;
		_idx = (_idx + 1) % frameCount;
	}
}

void FlipbookActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_flipbook == nullptr)
		return;

	const FlipbookInfo& info = _flipbook->GetInfo();
	Vec2 cameraPos = SceneManager::GetInstance()->GetCameraPos();

	::TransparentBlt(hdc,
		(int32)_pos.x - info.size.x / 2 - ((int32)cameraPos.x - GWinSizeX / 2),
		(int32)_pos.y - info.size.y / 2 - ((int32)cameraPos.y - GWinSizeY / 2),
		info.size.x,
		info.size.y,
		info.texture->GetDC(),
		(info.start + _idx) * info.size.x,
		info.line * info.size.y,
		info.size.x,
		info.size.y,
		info.texture->GetTransparent());
}

float FlipbookActor::GetFlipbookDuration()
{
	const FlipbookInfo& info = _flipbook->GetInfo();
	return info.duration;
}
