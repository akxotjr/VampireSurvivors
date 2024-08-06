#pragma once

enum class SceneType
{
	None,
	DevScene,
	EditScene,
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_OBJECT,
	LAYER_PROJECTILE,
	// ...
	LAYER_UI,

	LAYER_MAXCOUNT
};

enum Sight
{
	Right,
	Left
};

enum class ColliderType
{
	Box,
	Sphere,
};


enum COLLISION_LAYER_TYPE : uint8
{
	CLT_OBJECT,
	CLT_GROUND,
	CLT_WALL,
	// ...
};

enum Dir : uint8
{
	DIR_RIGHT		= 1,
	DIR_LEFT		= 2,
	DIR_UP			= 4,
	DIR_UPnRIGHT	= 5,
	DIR_UPnLEFT		= 6,
	DIR_DOWN		= 8,
	DIR_DOWNnRIGHT	= 9,
	DIR_DOWNnLEFT	= 10,
};