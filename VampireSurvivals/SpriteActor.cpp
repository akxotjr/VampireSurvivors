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

	RectF destRect = {
		_pos.x - size.x / 2 - (cameraPos.x - GWinSizeX / 2),
		_pos.y - size.y / 2 - (cameraPos.y - GWinSizeY / 2),
		(float)size.x, 
		(float)size.y};

	Graphics graphics(hdc);

	if (_dir.x != 0 && _dir.y != 0)
	{
		graphics.TranslateTransform(destRect.X + destRect.Width / 2, destRect.Y + destRect.Height / 2);
		graphics.RotateTransform(atan2(_dir.y, _dir.x) * 180 / PI);
		graphics.TranslateTransform(-(destRect.X + destRect.Width / 2), -(destRect.Y + destRect.Height / 2));
	}


	graphics.SetClip(destRect);

	graphics.DrawImage(
		_sprite->GetTexture()->GetGdiBitmap(),
		destRect,
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		_sprite->GetSize().x,
		_sprite->GetSize().y,
		UnitPixel
	);

}
