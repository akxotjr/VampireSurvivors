#include "pch.h"
#include "CameraComponent.h"
#include "Actor.h"
#include "SceneManager.h"

CameraComponent::CameraComponent()
{
	SetComponentType(CAMERA);
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Init()
{

}

void CameraComponent::Update()
{
	if (_owner == nullptr)
		return;

	Vec2 pos = _owner->GetPos();

	// TEMP
	//pos.x = ::clamp(pos.x, 0.f, 960.f);
	//pos.y = ::clamp(pos.y, 0.f, 720.f);

	SceneManager::GetInstance()->SetCameraPos(pos);
}

void CameraComponent::Render(HDC hdc)
{

}
