#pragma once
#include "SpriteActor.h"

class Sprite;
class Tilemap;

class Map : public SpriteActor
{
	using Super = SpriteActor;
public:
	Map();
	virtual ~Map() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

protected:
	Tilemap*	_tilemap = nullptr;
	//Sprite*		_sprite = nullptr;
};

