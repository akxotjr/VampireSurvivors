#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "Texture.h"
#include "SceneManager.h"

SpriteActor::SpriteActor()
{
}

SpriteActor::~SpriteActor()
{
}

void SpriteActor::Init()
{
	Super::Init();
}

void SpriteActor::Update()
{
	Super::Update();
}

void SpriteActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_sprite == nullptr) return;

	Vec2Int size = _sprite->GetSize();
	Vec2 cameraPos = SceneManager::GetInstance()->GetCameraPos();

	::TransparentBlt(hdc,
		(int32)_pos.x - size.x / 2 - ((int32)cameraPos.x - GWinSizeX / 2),
		(int32)_pos.y - size.y / 2 - ((int32)cameraPos.y - GWinSizeY / 2),
		size.x,
		size.y,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		_sprite->GetSize().x,
		_sprite->GetSize().y,
		_sprite->GetTransparent());

}
