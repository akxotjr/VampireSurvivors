#pragma once

enum class SceneType
{
	None,
	DevScene,
	EditScene,
	GameScene
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_PLAYER,
	LAYER_MONSTER,
	LAYER_LOOT,
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
	CLT_PLAYER,
	CLT_SKILL,
	CLT_MONSTER,
	CLT_GROUND,
	CLT_WALL,
	// ...
	CLT_MAX_COUNT
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