#include "pch.h"
#include "Projectile.h"
#include "SpriteActor.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Sprite.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::Init()
{
	Super::Init();
}

void Projectile::Update()
{
	Super::Update();

	Vec2 nextPos = _pos + _dir * _speed;
	Vec2 cameraPos = SceneManager::GetInstance()->GetCameraPos();
	//if ((cameraPos.x - GWinSizeX / 2) >= nextPos.x || (cameraPos.x + GWinSizeX / 2) <= nextPos.x || (cameraPos.y - GWinSizeY) >= nextPos.y || (cameraPos.y + GWinSizeY) <= nextPos.y)
	//{
	//	SceneManager::GetInstance()->GetCurrentScene()->RemoveActor(this);
	//}
	//else
	//{
		_pos = nextPos;
	//}
}

void Projectile::Render(HDC hdc)
{
	Super::Render(hdc);
}
